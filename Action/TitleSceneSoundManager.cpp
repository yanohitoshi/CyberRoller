#include "TitleSceneSoundManager.h"
#include "AudioResourceManager.h"
#include "MusicComponent.h"
#include "SoundEffectComponent.h"

TitleSceneSoundManager::TitleSceneSoundManager()
	: GameObject(false,Tag::AUDIO)
{
	bgm = new MusicComponent(this, "Assets/Sound/Bgm/Cyber01.wav");
	startSceneSound = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/Button/button.wav");
	isAvailableSelectInput = true;
	isPlayDecisionSound = false;
	bgm->Play();
}

TitleSceneSoundManager::~TitleSceneSoundManager()
{
}

void TitleSceneSoundManager::UpdateGameObject(float _deltaTime)
{
	if (!bgm->IsPlaying())
	{
	}
}

void TitleSceneSoundManager::GameObjectInput(const InputState& _keyState)
{
	// シーン決定ボタンが使用可能か
	if (isAvailableSelectInput)
	{

		// トリガーの情報を変数に入れる
		float leftTrigger = _keyState.Controller.GetLeftTrigger();
		float rightTrigger = _keyState.Controller.GetRightTrigger();

		// 入力状態を判定
		isPushDecisionSceneButton = _keyState.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_GUIDE) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_START) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_LEFTSTICK) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_RIGHTSTICK) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_LEFTSHOULDER) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_UP) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_DOWN) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_LEFT) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == Pressed ||
			leftTrigger == 1.0f || rightTrigger == 1.0f;

		// 入力されていたら
		if (isPushDecisionSceneButton)
		{
			// サウンドを鳴らす
			startSceneSound->Play();
			// 入力不可状態に変更
			isAvailableSelectInput = false;
			if (bgm->IsPlaying())
			{
				bgm->Stop();
			}
		}
	}

	if (isPushDecisionSceneButton)
	{
		isPlayDecisionSound = startSceneSound->IsPlaying();
	}
}
