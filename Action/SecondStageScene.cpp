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
	//ライトの設定(設定しないと何も映らない)
	// ライト情報初期化
	light = Vector3(0.1f, 0.1f, 0.1f);
	RENDERER->SetAmbientLight(light);
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(0.0f, 0.0f, 1.0f);
	dir.diffuseColor = Vector3(0.36f, 0.44f, 0.5f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);
	// メンバー変数初期化
	clearCount = 0;
	changeCount = 0;
	startScene = true;
	isContinueFlag = false;
	endFlag = false;
	lightDownFlag = true;

	// クリエイター生成
	SecondStageCreator* secondStageCreator = new SecondStageCreator(false,Tag::OTHER);

	//ステージ情報ファイルを開く
	if (!secondStageCreator->OpenFile())
	{
		//ステージを生成する(エネミーの初期位置情報も同時に)
		secondStageCreator->CreateStage();
		//プレイヤーの生成
		secondStageCreator->CreatePlayer();
	}

	// シーンUIを追加
	new SecondStageUI();

}

SecondStageScene::~SecondStageScene()
{
}

SceneState SecondStageScene::Update(const InputState& state)
{
	// シーンが始まったらライトを強くする
	if (startScene == true)
	{
		light += Vector3(0.01f, 0.01f, 0.01f);
		RENDERER->SetAmbientLight(light);
		if (light.x >= MAX_LIGHT)
		{
			startScene = false;
			RENDERER->SetAmbientLight(light);
		}
	}

	// ステージクリアしたらクリアカウントを取ってライトを落とす
	if (PlayerObject::GetNextSceneFlag() == true)
	{
		++clearCount;
		light -= Vector3(0.01f, 0.01f, 0.01f);
		RENDERER->SetAmbientLight(light);
	}

	// クリア状態かつクリアカウントが一定を超えたらシーンを切り替える
	if (clearCount >= CLEAR_TO_CHANGE_SCENE)
	{
		return SceneState::THIRD_SATGE_SCENE;
	}

	// タイムオーバー状態かつライトを一定まで落とす状態だったら
	if (CountDownFont::timeOverFlag == true && lightDownFlag == true)
	{
		// ライト固定
		light = Vector3(0.3f, 0.3f, 0.3f);
		RENDERER->SetAmbientLight(light);

		// Aボタンが押されたら
		if (state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed)
		{
			lightDownFlag = false;
			// コンテニュー遷移状態にする
			isContinueFlag = true;
		}

		// Bボタンが押されたら
		if (state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed)
		{
			lightDownFlag = false;
			// ゲームオーバー状態にする
			endFlag = true;
		}
	}

	// コンテニューかゲームオーバーが選択されたら
	if (isContinueFlag == true || endFlag == true)
	{
		// 遷移カウント開始
		++changeCount;
		if (changeCount >= CHOICE_CONTINUE_COUNT)
		{
			// コンテニューだったら明るくゲームオーバーだったら暗くする
			if (isContinueFlag == true)
			{
				// ライトアップ
				light += Vector3(0.01f, 0.01f, 0.01f);
				RENDERER->SetAmbientLight(light);
			}
			else if (endFlag == true)
			{
				// ライトダウン
				light -= Vector3(0.01f, 0.01f, 0.01f);
				RENDERER->SetAmbientLight(light);
			}
			if (changeCount >= CONTINUE_TO_CHANGE_SCENE)
			{
				// コンテニューだったらステージ最初へゲームオーバーだったらリザルト画面へ
				if (isContinueFlag == true)
				{
					// コンティニューされたらそのステージから始めるために
					// コンティニューされたかどうか判定するためのフラグを切り替える
					Game::SetContinueFlag(true);
					return SceneState::SECOND_SATGE_SCENE;
				}
				else if (endFlag == true)
				{
					return SceneState::RESULT_SCENE;
				}
			}
		}
	}

	// 一定時間操作がなかったらタイトルへ
	if (PlayerObject::GetReStartFlag() == true)
	{
		return SceneState::TITLE_SCENE;
	}

	return SceneState::SECOND_SATGE_SCENE;
}