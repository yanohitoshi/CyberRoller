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
	isEndDecisionSound = false;

	bgm = new MusicComponent(this, "Assets/Sound/Bgm/Cyber02.wav");
	changeSelectSceneSound = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/Button/button.wav");
	sceneDecisionSound = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/Button/button2.wav");
}

StageSelectSceneSoundManager::~StageSelectSceneSoundManager()
{
}

void StageSelectSceneSoundManager::UpdateGameObject(float _deltaTime)
{
}

void StageSelectSceneSoundManager::GameObjectInput(const InputState& _keyState)
{
	// シーン決定ボタンが押されているか
	bool pushDecisionSceneButton = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_RETURN) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed;

	if (pushDecisionSceneButton)
	{
		sceneDecisionSound->Play();
	}

	isEndDecisionSound = sceneDecisionSound->IsPlaying();

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

	if (!isAnalogStickSelect)
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
	bool pushSelectSceneButton = _keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Pressed ||
		_keyState.Keyboard.GetKeyState(SDL_SCANCODE_A) == Pressed ||
		_keyState.Keyboard.GetKeyState(SDL_SCANCODE_D) == Pressed;

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
