#include "ThirdStageScene.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "InputSystem.h"
#include "ThirdStageCreator.h"
#include "ThirdStageUI.h"
#include "CountDownFont.h"

ThirdStageScene::ThirdStageScene()
{
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
	ThirdStageCreator* thirdStageCreator = new ThirdStageCreator(false, Tag::OTHER);

	//ステージ情報ファイルを開く
	if (!thirdStageCreator->OpenFile())
	{
		//プレイヤーの生成
		playerObject = thirdStageCreator->CreatePlayer();
		//ステージを生成する
		thirdStageCreator->CreateStage();

	}

	// シーンUIを追加
	new ThirdStageUI(playerObject);

}

ThirdStageScene::~ThirdStageScene()
{
}

SceneState ThirdStageScene::Update(const InputState& state)
{
	// シーンが始まったらライトを強くする
	if (startScene == true)
	{
		light += CHANGE_LIGHT_SPEED;
		RENDERER->SetAmbientLight(light);
		if (light.x >= MAX_LIGHT)
		{
			startScene = false;
			RENDERER->SetAmbientLight(light);
		}
	}

	// ステージクリアしたらクリアカウントを取ってライトを落とす
	if (playerObject->GetNextSceneFlag() == true)
	{
		++clearCount;
		light -= CHANGE_LIGHT_SPEED;
		RENDERER->SetAmbientLight(light);
	}

	// クリア状態かつクリアカウントが一定を超えたらシーンを切り替える
	if (playerObject->GetNextSceneFlag() == true && clearCount >= CLEAR_TO_CHANGE_SCENE)
	{
		return SceneState::FINAL_STAGE_SCENE;
	}

	// タイムオーバー状態かつライトを一定まで落とす状態だったら
	if (CountDownFont::timeOverFlag == true && lightDownFlag == true)
	{
		// ライト固定
		light = TIMEOVERS_LIGHT;
		RENDERER->SetAmbientLight(light);

		// Aボタンが押されたら
		if (state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed)
		{
			// コンテニュー遷移状態にする
			lightDownFlag = false;
			isContinueFlag = true;
		}
		// Bボタンが押されたら
		if (state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed)
		{
			// ゲームオーバー状態にする
			lightDownFlag = false;
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
				light += CHANGE_LIGHT_SPEED;
				RENDERER->SetAmbientLight(light);
			}
			else if (endFlag == true)
			{
				// ライトダウン
				light -= CHANGE_LIGHT_SPEED;
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
					return SceneState::THIRD_SATGE_SCENE;
				}
				else if (endFlag == true)
				{
					return SceneState::RESULT_SCENE;
				}
			}
		}
	}

	// 一定時間操作がなかったらタイトルへ
	if (playerObject->GetReStartFlag() == true)
	{
		return SceneState::TITLE_SCENE;
	}

	// シーン変更しない場合今のシーンを返す
	return SceneState::THIRD_SATGE_SCENE;
}