//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "FinalStageScene.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "FinalStageCreator.h"
#include "FinalStageUI.h"
#include "CountDownFont.h"
#include "CollectionObject.h"

/*
@fn コンストラクタ
@brief  Sceneの生成を行う
*/
FinalStageScene::FinalStageScene()
	: FinalClearToChangeScene(360)
{
	// ライト情報初期化
	light = Vector3(0.1f, 0.1f, 0.1f);
	RENDERING_OBJECT_MANAGER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERING_OBJECT_MANAGER->GetDirectionalLight();
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
	state = SceneState::FINAL_STAGE_SCENE;

	// クリエイター生成
	FinalStageCreator* finalStageCreator = new FinalStageCreator(false, Tag::OTHER);

	//ステージ情報ファイルを開く
	if (!finalStageCreator->OpenFile())
	{
		//プレイヤーの生成
		playerObject = finalStageCreator->CreatePlayer();
		//ステージを生成する
		finalStageCreator->CreateStage();
	}

	CollectionObject* firstCollection = finalStageCreator->FindCollectionObject(CollectionTag::FIRST);
	CollectionObject* secondCollection = finalStageCreator->FindCollectionObject(CollectionTag::SECOND);
	CollectionObject* thirdCollection = finalStageCreator->FindCollectionObject(CollectionTag::THIRD);

	// シーンUIを追加
	new FinalStageUI(playerObject, firstCollection, secondCollection, thirdCollection);

}

/*
@fn デストラクタ
@brief  sceneの削除を行う
*/
FinalStageScene::~FinalStageScene()
{
}

/*
@fn　シーンのアップデート関数
@brief	シーンの更新処理を行う
@param	入力情報
@return シーンの遷移を判定するためのenum型のSceneState
*/
SceneState FinalStageScene::Update(const InputState& _inputState)
{
	// シーンが始まったらライトを強くする
	if (startScene == true)
	{
		// シーン開始時のライトアップ処理
		StartSceneLightUpProcess();
	}

	// 最終ステージではライトを落とさないためクリアカウントのみ数える
	if (playerObject->GetClearFlag() == true)
	{
		// クリアカウント
		++clearCount;
	}

	// クリア状態かつクリアカウントが一定を超えたらシーンを切り替える
	if (clearCount >= FinalClearToChangeScene)
	{
		state = SceneState::RESULT_SCENE;
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
		SceneStateChangeAtContinue(SceneState::FINAL_STAGE_SCENE);
	}
	// 一定時間操作がなかったらタイトルへ
	if (playerObject->GetRestartFlag() == true)
	{
		state = SceneState::TITLE_SCENE;
	}

	// シーン変更しない場合今のシーンを返す
	return state;
}