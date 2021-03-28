#include "PlayerObjectStateJumpStart.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateJumpStart::PlayerObjectStateJumpStart()
{
}

PlayerObjectStateJumpStart::~PlayerObjectStateJumpStart()
{
}

PlayerState PlayerObjectStateJumpStart::Update(PlayerObject* _owner, float _deltaTime)
{
	velocity.z -= PlayerObject::GetGravity() * _deltaTime;

	if (velocity.z <= -2000.0f)
	{
		velocity.z = -2000.0f;
	}

	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	if (endFlag == true)
	{
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

	if (_owner->GetOnGround() == true && endFlag == true)
	{
		state = PlayerState::PLAYER_STATE_JUMPEND;
	}

	if (_owner->GetDeadFlag())
	{
		state = PlayerState::PLAYER_STATE_DEAD;
	}

	return state;
}

void PlayerObjectStateJumpStart::Input(PlayerObject* _owner, const InputState& _keyState)
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
	if (Math::Abs(axis.x) > 0.0f || Math::Abs(axis.y) > 0.0f)
	{
		_owner->SetTmpCharaForwardVec(_owner->GetCharaForwardVec());
		// 方向キーの入力値とカメラの向きから、移動方向を決定
		// charaForwardVec = forwardVec * axis.x + rightVec * axis.y;
		Vector3 forward = _owner->GetForwardVec() * axis.x + _owner->GetRightVec() * axis.y;
		forward.Normalize();
		_owner->SetCharaForwardVec(forward);

		velocity.x = _owner->GetCharaForwardVec().x * _owner->GetMoveSpeed() * 2.0f;
		velocity.y = _owner->GetCharaForwardVec().y * _owner->GetMoveSpeed() * 2.0f;


		if (_owner->GetTmpCharaForwardVec() != _owner->GetCharaForwardVec())
		{
			Vector3 tmpRotateVec = _owner->GetCharaForwardVec();
			tmpRotateVec.Normalize();

			//回転
			Vector3 rotatioin = Vector3::Lerp(forward, tmpRotateVec, 0.2f);
			_owner->RotateToNewForward(rotatioin);
			_owner->SetRotateVec(rotatioin);

		}

	}

	if (_owner->GetIsAvailableJumpKey() == true && _owner->GetIsJumping() == true || _owner->GetSwitchJumpFlag() == true && _owner->GetIsAvailableJumpKey() == true)
	{ 

		if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Held ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Held ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Held ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Held ||
			_owner->GetIsAvailableJumpKey() == true)
		{
			++jumpFrameCount;
			_owner->SetJumpFlag(true);
			float jumpPower = _owner->GetJumpPower();
			velocity.z = jumpPower;

			if (8 > jumpFrameCount && _owner->GetSwitchJumpFlag() == false)
			{
				_owner->SetJumpPower(jumpPower + 100.0f );
			}
			else if (_owner->GetSwitchJumpFlag() == true && 16 > jumpFrameCount )
			{
				_owner->SetJumpPower(jumpPower + 100.0f);
			}
			else
			{
				_owner->SetIsAvailableJumpKey(false);
				_owner->SetIsJumping(false);
				endFlag = true;
			}

		}
	}

	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Released ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Released ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Released ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Released)
	{
		_owner->SetIsAvailableJumpKey(false);
		_owner->SetIsJumping(false);
		_owner->SetJumpPower(_owner->GetFirstJumpPower());
		endFlag = true;
	}
}

void PlayerObjectStateJumpStart::Enter(PlayerObject* _owner, float _deltaTime)
{
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPSTART),0.6f);
	state = PlayerState::PLAYER_STATE_JUMPSTART;
	jumpFrameCount = _owner->GetJumpFrameCount();
	velocity = _owner->GetVelocity();

	endFlag = false;
}
