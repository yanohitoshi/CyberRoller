#include "PlayerObjectStateJunpEndToRun.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateJunpEndToRun::PlayerObjectStateJunpEndToRun()
{
}

PlayerObjectStateJunpEndToRun::~PlayerObjectStateJunpEndToRun()
{
}

PlayerState PlayerObjectStateJunpEndToRun::Update(PlayerObject* _owner, float _deltaTime)
{

	// positionに速度を足してキャラクターを動かす
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	if (!skeletalMeshComponent->IsPlaying())
	{
		if (_owner->GetInputFlag())
		{
			state = PlayerState::PLAYER_STATE_RUN_START;
		}
		else
		{
			state = PlayerState::PLAYER_STATE_IDLE;
		}
	}

	if (_owner->GetIsJumping() || _owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

	_owner->SetMoveSpeed(moveSpeed);

	// 更新されたstateを返す
	return state;
}

void PlayerObjectStateJunpEndToRun::Input(PlayerObject* _owner, const InputState& _keyState)
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
			_owner->SetTmpCharaForwardVec(_owner->GetCharaForwardVec());

			// 方向キーの入力値とカメラの向きから、移動方向を決定
			Vector3 forward = _owner->GetForwardVec() * axis.x + _owner->GetRightVec() * axis.y;
			forward.Normalize();


			moveSpeed += _owner->GetMovePower();

			if (moveSpeed >= MaxMoveSpeed)
			{
				moveSpeed = MaxMoveSpeed;
			}

			velocity.x = forward.x * moveSpeed;
			velocity.y = forward.y * moveSpeed;


			if (_owner->GetTmpCharaForwardVec() != forward)
			{
				Vector3 tmpRotateVec = _owner->GetCharaForwardVec();
				tmpRotateVec.Normalize();

				//回転
				Vector3 rotatioin = Vector3::Lerp(forward, tmpRotateVec, 0.01f);
				_owner->RotateToNewForward(rotatioin);
				_owner->SetRotateVec(rotatioin);

			}

			_owner->SetCharaForwardVec(forward);
			_owner->SetMoveSpeed(moveSpeed);

		}
		else
		{
			if (moveSpeed >= 0.0f)
			{
				moveSpeed -= 75.0f;
			}

			velocity.x = _owner->GetCharaForwardVec().x * moveSpeed;
			velocity.y = _owner->GetCharaForwardVec().y * moveSpeed;

			_owner->SetInputFlag(false);
		}

		if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed)
		{
			_owner->SetJumpFlag(true);
			_owner->SetIsJumping(true);
		}
	}
}

void PlayerObjectStateJunpEndToRun::Enter(PlayerObject* _owner, float _deltaTime)
{
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPEND_TO_RUN));
	state = PlayerState::PLAYER_STATE_JUMPEND_TO_RUN;

	_owner->SetJumpPower(_owner->GetFirstJumpPower());
	moveSpeed = _owner->GetMoveSpeed();
	velocity = _owner->GetVelocity();
	velocity.z = 0.0f;
	inputDeadSpace = _owner->GetDeadSpace();

}
