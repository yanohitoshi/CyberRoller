//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "BaseScene.h"
#include "RenderingObjectManager.h"
#include "PlayerObject.h"

/*
@fn シーン開始時のライトアップ関数
*/
void BaseScene::StartSceneLightUp()
{
	// ライトの数値を明るくする
	light += ChangeLightSpeed;
	// レンダラーに値をセット
	RENDERING_OBJECT_MANAGER->SetAmbientLight(light);

	// ライトの数値が一定以上になったら
	if (light.x >= MaxLight)
	{
		// シーン開始フラグをfalseに変更
		startScene = false;
		// 最終の値をセット
		RENDERING_OBJECT_MANAGER->SetAmbientLight(light);
	}
}

/*
@fn クリアしたかのチェックとクリアカウントを数える処理関数
@param _playerObject シーンに存在するプレイヤーのポインタ
*/
void BaseScene::SceneClearCount(PlayerObject* _playerObject)
{
	isSceneClear = _playerObject->GetClearFlag();
	if (isSceneClear)
	{
		++clearCount;
		light -= ChangeLightSpeed;
		RENDERING_OBJECT_MANAGER->SetAmbientLight(light);
	}
}

/*
@fn コンティニュー選択処理関数
@param _inputState 入力情報
*/
void BaseScene::ContinueSelect(const InputState& state)
{
	// ライト固定
	light = TimeoversLight;
	RENDERING_OBJECT_MANAGER->SetAmbientLight(light);

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
		isEndFlag = true;
	}
}

/*
@fn コンティニュー選択時のライト遷移関数
*/
void BaseScene::LightTransitionAtContinue()
{
	// 遷移カウント開始
	++changeCount;

	// コンティニュー選択後の
	if (changeCount >= ChoiceContinueCount)
	{
		// コンテニューだったら明るくゲームオーバーだったら暗くする
		if (isContinueFlag == true)
		{
			// ライトアップ
			light += ChangeLightSpeed;
			RENDERING_OBJECT_MANAGER->SetAmbientLight(light);
		}
		else if (isEndFlag == true)
		{
			// ライトダウン
			light -= ChangeLightSpeed;
			RENDERING_OBJECT_MANAGER->SetAmbientLight(light);
		}

	}
}

/*
@fn コンティニュー選択後のシーンステータス変更処理関数
@param _nowScene コンティニューが選択された場合そのシーンのステータスが必要なため今のステータスをもらう
*/
void BaseScene::SceneStateChangeAtContinue(SceneState _nowScene)
{
	// コンテニューだったらステージ最初へゲームオーバーだったらリザルト画面へ
	if (isContinueFlag == true)
	{
		// コンティニューされたらそのステージから始めるために
		// コンティニューされたかどうか判定するためのフラグを切り替える
		Game::SetContinueFlag(true);
		state = _nowScene;
	}
	else if (isEndFlag == true)
	{
		state = SceneState::RESULT_SCENE;
	}
}