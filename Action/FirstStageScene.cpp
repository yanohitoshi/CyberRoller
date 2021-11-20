//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "FirstStageScene.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "FirstStageCreator.h"
#include "FirstStageUI.h"
#include "CountDownFont.h"
#include "CollectionObject.h"

/*
@fn コンストラクタ
@brief  Sceneの生成を行う
*/
FirstStageScene::FirstStageScene()
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
	state = SceneState::FIRST_SATGE_SCENE;

	// クリエイター生成
	FirstStageCreator* secondStageCreator = new FirstStageCreator(false,Tag::OTHER);

	//ステージ情報ファイルを開く
	if (!secondStageCreator->OpenFile())
	{
		//プレイヤーの生成
		playerObject = secondStageCreator->CreatePlayer();
		//ステージを生成する
		secondStageCreator->CreateStage();
	}

	CollectionObject* firstCollection = secondStageCreator->FindCollectionObject(CollectionTag::FIRST);
	CollectionObject* secondCollection = secondStageCreator->FindCollectionObject(CollectionTag::SECOND);
	CollectionObject* thirdCollection = secondStageCreator->FindCollectionObject(CollectionTag::THIRD);

	// シーンUIを追加
	new FirstStageUI(playerObject,firstCollection,secondCollection,thirdCollection);
}

/*
@fn デストラクタ
@brief  sceneの削除を行う
*/
FirstStageScene::~FirstStageScene()
{
}

/*
@fn　シーンのアップデート関数
@brief	シーンの更新処理を行う
@param	入力情報
@return シーンの遷移を判定するためのenum型のSceneState
*/
SceneState FirstStageScene::Update(const InputState& _inputState)
{
	// シーンが始まったらライトを強くする
	if (startScene == true)
	{
		// シーン開始時のライトアップ処理
		StartSceneLightUpProcess();
	}

	// クリアしたかのチェックとクリアカウントを数える処理関数
	SceneClearCountProcess(playerObject);

	// クリア状態かつクリアカウントが一定を超えたらシーンを切り替える
	if (clearCount >= ClearToChangeSceneTime)
	{
		// 次のシーンに変更
		state = SceneState::SECOND_SATGE_SCENE;
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
		SceneStateChangeAtContinue(SceneState::FIRST_SATGE_SCENE);
	}

	// 一定時間操作がなかったらタイトルへ
	if (playerObject->GetRestartFlag() == true)
	{
		state = SceneState::TITLE_SCENE;
	}

	// 更新後のシーンステータスを返す
	return state;
}