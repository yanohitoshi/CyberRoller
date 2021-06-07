#include "SecondStageScene.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "SecondStageCreator.h"
#include "SecondStageUI.h"
#include "CountDownFont.h"

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
	SecondStageCreator* secondStageCreator = new SecondStageCreator(false,Tag::OTHER);

	//ステージ情報ファイルを開く
	if (!secondStageCreator->OpenFile())
	{
		//プレイヤーの生成
		playerObject = secondStageCreator->CreatePlayer();
		//ステージを生成する
		secondStageCreator->CreateStage();
	}

	// シーンUIを追加
	new SecondStageUI(playerObject);

}

SecondStageScene::~SecondStageScene()
{
}

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

	// クリア状態かつクリアカウントが一定を超えたらシーンを切り替える
	if (clearCount >= ClearToChangeSceneTime)
	{
		// 次のシーンに変更
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
	if (playerObject->GetReStartFlag() == true)
	{
		state = SceneState::TITLE_SCENE;
	}

	// 更新後のシーンステータスを返す
	return state;
}