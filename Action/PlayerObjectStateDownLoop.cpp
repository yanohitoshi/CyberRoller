#include "PlayerObjectStateDownLoop.h"
#include "SkeletalMeshComponent.h"
PlayerObjectStateDownLoop::PlayerObjectStateDownLoop()
{
}

PlayerObjectStateDownLoop::~PlayerObjectStateDownLoop()
{
}

PlayerState PlayerObjectStateDownLoop::Update(PlayerObject* _owner, float _deltaTime)
{
	// 入力フラグがtrueになった時
	if (isInput)
	{
		// 入力状態を見てコンティニュー状態を確認
		ChackContinueProcess();
	}

	// 更新されたstateを返す
	return state;
}

void PlayerObjectStateDownLoop::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// もし、コントローラーのAボタンまたはキーボードのCボタンが押されたら
	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
		_keyState.Keyboard.GetKeyDownValue(SDL_SCANCODE_C) == true)
	{
		// 入力フラグをtrueに変更
		isInput = true;
		// コンティニューフラグをtrueに変更
		isContinue = true;
	}
	// もし、コントローラーのBボタンまたはキーボードのZボタンが押されたら
	else if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
			 _keyState.Keyboard.GetKeyDownValue(SDL_SCANCODE_Z) == true)
	{
		// 入力フラグのみをtrueに変更
		isInput = true;
	}
	
}

void PlayerObjectStateDownLoop::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DOWN_LOOP));
	// stateをダウンループ状態にして保存
	state = PlayerState::PLAYER_STATE_DOWN_LOOP;
	// コンティニューフラグを初期化
	isContinue = false;
	// 入力があったかどうかフラグを初期化
	isInput = false;
}

void PlayerObjectStateDownLoop::ChackContinueProcess()
{
	// コンティニューフラグがtrueだったら
	if (isContinue)
	{
		// コンティニューが選択された状態に変更
		state = PlayerState::PLAYER_STATE_DOWN_UP;
	}
	else // コンティニューされていなかったら
	{
		// ゲームオーバー状態に変更
		state = PlayerState::PLAYER_STATE_DOWN_OVER;
	}
}
