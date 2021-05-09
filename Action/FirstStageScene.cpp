#include "FirstStageScene.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "FirstStageUI.h"
#include "FirstStageCreator.h"


FirstStageScene::FirstStageScene()
{
	// ライト情報初期化
	light = Vector3(0.1f, 0.1f, 0.1f);
	RENDERER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(0.0f, 0.0f, 0.7f);
	dir.diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.specColor = Vector3(1.0f, 1.0f, 1.0f);

	// メンバー変数初期化
	clearCount = 0;
	startScene = true;

	// クリエイター生成
	FirstStageCreator* firstStageCreator = new FirstStageCreator(false,Tag::OTHER);

	//ステージ情報ファイルを開く
	if (!firstStageCreator->OpenFile())
	{
		//プレイヤーの生成
		playerObject = firstStageCreator->CreatePlayer();
		//ステージを生成する
		firstStageCreator->CreateStage();
	}

	// シーンUIを追加
	new FirstStageUI();
}

FirstStageScene::~FirstStageScene()
{
}

SceneState FirstStageScene::Update(const InputState& state)
{
	// シーンが始まったらライトを強くする
	if (startScene == true)
	{
		light += ChangeLightSpeed;
		RENDERER->SetAmbientLight(light);

		if (light.x >= MaxLight)
		{
			startScene = false;
			RENDERER->SetAmbientLight(light);
		}
	}

	// ステージクリアしたらクリアカウントを取ってライトを落とす
	if (playerObject->GetNextSceneFlag() == true)
	{
		++clearCount;
		light -= ChangeLightSpeed;
		RENDERER->SetAmbientLight(light);
	}

	// クリア状態かつクリアカウントが一定を超えたらシーンを切り替える
	if (playerObject->GetNextSceneFlag() == true && clearCount >= ClearToChangeScene)
	{
		return SceneState::SECOND_SATGE_SCENE;
	}

	// 一定時間操作がなかったらタイトルへ
	if (playerObject->GetReStartFlag() == true)
	{
		return SceneState::TITLE_SCENE;
	}

	// シーン変更しない場合今のシーンを返す
	return SceneState::FIRST_SATGE_SCENE;
}