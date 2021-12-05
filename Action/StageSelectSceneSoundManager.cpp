//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "StageSelectSceneSoundManager.h"
#include "SoundEffectComponent.h"
#include "MusicComponent.h"

/*
@fn コンストラクタ
@param 親クラスのシーンクラスのポインタ
*/
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

	// BGMを生成
	bgm = new MusicComponent(this, "Assets/Sound/Bgm/StageSelect/StageSelect.wav");

	// サウンドエフェクトを生成
	changeSelectSceneSound = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/Button/Cursor.wav");
	sceneDecisionSound = new SoundEffectComponent(this, "Assets/Sound/SoundEffect/Button/button.wav");
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
StageSelectSceneSoundManager::~StageSelectSceneSoundManager()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void StageSelectSceneSoundManager::UpdateGameObject(float _deltaTime)
{
	// 再生されていなかったら
	if (!bgm->IsPlaying())
	{
		// 再生する
		bgm->Play();
	}
}

/*
@fn 入力を引数で受け取る更新関数
@brief 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
@param	_keyState 入力情報
*/
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

	// 決定ボタンが押されていたら
	if (isPushDecisionSceneButton)
	{
		// 再生されているかを更新
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