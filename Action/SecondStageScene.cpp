//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "SecondStageScene.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "SecondStageCreator.h"
#include "SecondStageUI.h"
#include "CountDownFont.h"
#include "CollectionObject.h"

/*
@fn コンストラクタ
@brief  Sceneの生成を行う
*/
SecondStageScene::SecondStageScene()
{
	// ライト情報初期化
	light = Vector3(0.1f, 0.1f, 0.1f);
	RENDERER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(0.5f, 0.5f, 0.8f);
	dir.diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// メンバー変数初期化
	clearCount = 0;
	changeCount = 0;
	startScene = true;
	isContinueFlag = false;
	endFlag = false;
	lightDownFlag = true;
	state = SceneState::SECOND_SATGE_SCENE;

	// クリエイター生成
	SecondStageCreator* thirdStageCreator = new SecondStageCreator(false, Tag::OTHER);

	//ステージ情報ファイルを開く
	if (!thirdStageCreator->OpenFile())
	{
		//プレイヤーの生成
		playerObject = thirdStageCreator->CreatePlayer();
		//ステージを生成する
		thirdStageCreator->CreateStage();
	}

	CollectionObject* firstCollection = thirdStageCreator->FindCollectionObject(CollectionTag::FIRST);
	CollectionObject* secondCollection = thirdStageCreator->FindCollectionObject(CollectionTag::SECOND);
	CollectionObject* thirdCollection = thirdStageCreator->FindCollectionObject(CollectionTag::THIRD);

	// シーンUIを追加
	new SecondStageUI(playerObject, firstCollection, secondCollection, thirdCollection);
}

/*
@fn デストラクタ
@brief  sceneの削除を行う
*/
SecondStageScene::~SecondStageScene()
{
}

/*
@fn　シーンのアップデート関数
@brief	シーンの更新処理を行う
@param	入力情報
@return シーンの遷移を判定するためのenum型のSceneState
*/
SceneState SecondStageScene::Update(const InputState& _inputState)
{
	// シーンが始まったらライトを強くする
	if (startScene == true)
	{
		// シーン開始時のライトアップ処理
		StartSceneLightUpProcess();
	}

	// クリアしたかのチェックとクリアカウントを数える処理関数
	SceneClearCountProcess(playerObject);

	// クリアカウントが一定を超えたらシーンを切り替える
	if (clearCount >= ClearToChangeSceneTime)
	{
		state = SceneState::THIRD_SATGE_SCENE;
	}

	// タイムオーバー状態かつライトを一定まで落とす状態だったら
	if (CountDownFont::GetTimeOverFlag() == true && lightDownFlag == true)
	{
		// コンティニュー選択処理
		ContinueSelectProcess(_inputState);
	}

	 // コンテニューかゲームオーバーが選択されたら
	if (isContinueFlag == true || endFlag == true)
	{
		// コンティニュー選択時のライト遷移処理
		LightTransitionAtContinue();
	}

	// コンティニュー選択後のシーン切り替えカウントが一定以上になったら
	if (changeCount >= ContinueToChangeScene)
	{
		// シーンステータス切り替え処理
		SceneStateChangeAtContinue(SceneState::SECOND_SATGE_SCENE);
	}

	// 一定時間操作がなかったらタイトルへ
	if (playerObject->GetRestartFlag() == true)
	{
		state = SceneState::TITLE_SCENE;
	}

	// 更新後のシーンステータスを返す
	return state;
}