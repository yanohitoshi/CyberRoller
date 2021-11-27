//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TutorialStageScene.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "TutorialStageUI.h"
#include "TutorialStageCreator.h"

/*
@fn コンストラクタ
@brief  Sceneの生成を行う
*/
TutorialStageScene::TutorialStageScene()
{
	// ライト情報初期化
	light = Vector3(0.1f, 0.1f, 0.1f);
	RENDERING_OBJECT_MANAGER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERING_OBJECT_MANAGER->GetDirectionalLight();
	dir.direction = Vector3(0.5f, 0.5f, 0.8f);
	dir.diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.specColor = Vector3(1.0f, 1.0f, 1.0f);

	// メンバー変数初期化
	clearCount = 0;
	startScene = true;

	// クリエイター生成
	TutorialStageCreator* tutorialStageCreator = new TutorialStageCreator(false,Tag::OTHER);

	//ステージ情報ファイルを開く
	if (!tutorialStageCreator->OpenFile())
	{
		//プレイヤーの生成
		playerObject = tutorialStageCreator->CreatePlayer();
		//ステージを生成する
		tutorialStageCreator->CreateStage();
	}

	// シーンUIを追加
	new TutorialStageUI();
}

/*
@fn デストラクタ
@brief  sceneの削除を行う
*/
TutorialStageScene::~TutorialStageScene()
{
}

/*
@fn　シーンのアップデート関数
@brief	シーンの更新処理を行う
@param	入力情報
@return シーンの遷移を判定するためのenum型のSceneState
*/
SceneState TutorialStageScene::Update(const InputState& _inputState)
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
		return SceneState::STAGE_SELECT_SCENE;
	}

	// 一定時間操作がなかったらタイトルへ
	if (playerObject->GetRestartFlag() == true)
	{
		return SceneState::TITLE_SCENE;
	}

	// シーン変更しない場合今のシーンを返す
	return SceneState::TUTORIAL_SATGE_SCENE;
}