#include "StageSelectSceneSoundManager.h"
#include "SoundEffectComponent.h"
#include "MusicComponent.h"

StageSelectSceneSoundManager::StageSelectSceneSoundManager()
	: GameObject(false, Tag::AUDIO)
	, InputDeadSpace(0.3f)
{
	// 変数初期化
	isAnalogStickSelect = false;
	selectCount = 0;
	isPlayDecisionSound = false;
	isPushDecisionSceneButton = false;
	isAvailableSelectInput = true;
	bgm = new MusicComponent(this, "Assets/Sound/Bgm/Cyber02.wav");
	changeSelectSceneSound = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/Button/button2.wav");
	sceneDecisionSound = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/Button/button.wav");
}

StageSelectSceneSoundManager::~StageSelectSceneSoundManager()
{
}

void StageSelectSceneSoundManager::UpdateGameObject(float _deltaTime)
{
}

void StageSelectSceneSoundManager::GameObjectInput(const InputState& _keyState)
{
	// シーン決定ボタンが使用可能か
	if (isAvailableSelectInput)
	{
		// 入力状態を判定
		isPushDecisionSceneButton = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_RETURN) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed;

		// 入力されていたら
		if (isPushDecisionSceneButton)
		{
			// サウンドを鳴らす
			sceneDecisionSound->Play();
			// 入力不可状態に変更
			isAvailableSelectInput = false;
		}
	}

	if (isPushDecisionSceneButton)
	{
		isPlayDecisionSound = sceneDecisionSound->IsPlaying();
	}

	if (isAnalogStickSelect)
	{
		++selectCount;

		if (selectCount >= 30)
		{
			isAnalogStickSelect = false;
			selectCount = 0;
		}
	}

	// アナログスティックが傾いているかどうか
	bool inclineSelectSceneStick = false;

	if (!isAnalogStickSelect && isAvailableSelectInput)
	{
		// コントローラのアナログスティックの入力情報を計算する
		float ALX = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTX);
		float ALY = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTY);

		//アナログスティックのキー入力を取得
		Vector2 Axis = Vector2(0.0f, 0.0f);
		Axis = _keyState.Controller.GetLAxisLeftVec();

		//実際に動かしたい軸がずれているので補正
		Vector3 axis = Vector3(Axis.y * -1.0f, Axis.x * -1.0f, 0.0f);

		// 取得した数値を見てデッドスペース外だったら入力処理を行う
		if (Math::Abs(axis.y) > InputDeadSpace && !isAnalogStickSelect)
		{
			inclineSelectSceneStick = true;
			isAnalogStickSelect = true;
		}
	}

	// シーン選択ボタンが傾いているかどうか
	bool pushSelectSceneButton = false;
	if (isAvailableSelectInput)
	{
		pushSelectSceneButton = _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Pressed ||
			_keyState.Keyboard.GetKeyState(SDL_SCANCODE_A) == Pressed ||
			_keyState.Keyboard.GetKeyState(SDL_SCANCODE_D) == Pressed;
	}

	// シーン選択ボタンが押されるかStickが傾いていたら
	if (pushSelectSceneButton || inclineSelectSceneStick)
	{
		if (changeSelectSceneSound->IsPlaying())
		{
			changeSelectSceneSound->Stop();
		}

		// サウンドを鳴らす
		changeSelectSceneSound->Play();
	}

}
