#include "PlayerObjectStateIdlingDance.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

bool PlayerObjectStateIdlingDance::isDancing = false;

PlayerObjectStateIdlingDance::PlayerObjectStateIdlingDance()
{
}

PlayerObjectStateIdlingDance::~PlayerObjectStateIdlingDance()
{
}

PlayerState PlayerObjectStateIdlingDance::Update(PlayerObject* _owner, float _deltaTime)
{
	// positionに速度を足してキャラクターを動かす
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);


	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
		isDancing = false;
	}
	else if (_owner->GetInputFlag())
	{
		state = PlayerState::PLAYER_STATE_RUN_START;
		isDancing = false;
	}
	else if (_owner->GetIsJumping() || _owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		state = PlayerState::PLAYER_STATE_JUMPSTART;
		isDancing = false;
	}

	if (_owner->GetDeadFlag())
	{
		state = PlayerState::PLAYER_STATE_DEAD;
		isDancing = false;
	}

	if (CountDownFont::timeOverFlag == true)
	{
		state = PlayerState::PLAYER_STATE_DOWNSTART;
		isDancing = false;
	}

	// 更新されたstateを返す
	return state;
}

void PlayerObjectStateIdlingDance::Input(PlayerObject* _owner, const InputState& _keyState)
{

	if (_owner->GetIsAvailableInput())
	{
		//Axisの値をとる32700~-32700
		float ALX = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTX);
		float ALY = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTY);

		//アナログスティックのキー入力を取得
		Vector2 Axis = Vector2(0.0f, 0.0f);
		Axis = _keyState.Controller.GetLAxisLeftVec();

		//実際に動かしたい軸がずれているので補正
		Vector3 axis = Vector3(Axis.y * -1.0f, Axis.x * -1.0f, 0.0f);

		//入力があるか
		if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
		{
			_owner->SetInputFlag(true);
		}
		else
		{
			_owner->SetInputFlag(false);
		}

		if (_owner->GetOnGround() == true && _owner->GetJumpFlag() == false)
		{
			if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
				_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
				_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
				_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed ||
				_owner->GetSwitchJumpFlag() == true)
			{
				_owner->SetJumpFlag(true);
				_owner->SetIsJumping(true);
			}
		}
	}
}

void PlayerObjectStateIdlingDance::Enter(PlayerObject* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_IDLE_DANCE));
	// stateをダンス状態にして保存
	state = PlayerState::PLAYER_STATE_IDLE_DANCE;

	isDancing = true;
}
