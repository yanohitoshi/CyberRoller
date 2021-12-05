//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ResultSceneSoundManager.h"
#include "AudioResourceManager.h"
#include "MusicComponent.h"
#include "SoundEffectComponent.h"

/*
@fn コンストラクタ
@param 親クラスのシーンクラスのポインタ
*/
ResultSceneSoundManager::ResultSceneSoundManager()
	: GameObject(false, Tag::AUDIO)
{
	bgm = new MusicComponent(this, "Assets/Sound/Bgm/Result/Result.wav");
	startSceneSound = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/Button/button.wav");
	isAvailableSelectInput = true;
	isPlayDecisionSound = false;
	bgm->Play();
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
ResultSceneSoundManager::~ResultSceneSoundManager()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void ResultSceneSoundManager::UpdateGameObject(float _deltaTime)
{
}

/*
@fn 入力を引数で受け取る更新関数
@brief 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
@param	_keyState 入力情報
*/
void ResultSceneSoundManager::GameObjectInput(const InputState& _keyState)
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