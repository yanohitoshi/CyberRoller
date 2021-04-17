#include "PlayerObjectStateJumpLoop.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateJumpLoop::PlayerObjectStateJumpLoop()
{
}

PlayerObjectStateJumpLoop::~PlayerObjectStateJumpLoop()
{
}

PlayerState PlayerObjectStateJumpLoop::Update(PlayerObject* _owner, float _deltaTime)
{
	++jumpLoopCount;

	velocity.z -= PlayerObject::GetGravity() * _deltaTime;

	if (velocity.z <= -2000.0f)
	{
		velocity.z = -2000.0f;
	}

	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	if (animChangeFlag == true && velocity.z <= 0.0f)
	{
		skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPLOOP));
		animChangeFlag = false;
	}

	if (_owner->GetOnGround() == true && _owner->GetInputFlag() && move >= 600.0f)
	{
		state = PlayerState::PLAYER_STATE_JUMPEND_TO_RUN;
	}
	else if (_owner->GetOnGround() == true)
	{
		state = PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE;
	}

	if (_owner->GetDeadFlag())
	{
		state = PlayerState::PLAYER_STATE_DEAD;
	}

	if (CountDownFont::timeOverFlag == true)
	{
		state = PlayerState::PLAYER_STATE_DOWNSTART;
	}

	_owner->SetVelocity(velocity);
	_owner->SetMoveSpeed(move);

	// 更新されたstateを返す
	return state;
}

void PlayerObjectStateJumpLoop::Input(PlayerObject* _owner, const InputState& _keyState)
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
			Vector3 tmpForward = _owner->GetCharaForwardVec();
			_owner->SetTmpCharaForwardVec(tmpForward);

			// 方向キーの入力値とカメラの向きから、移動方向を決定
			Vector3 forward = _owner->GetForwardVec() * axis.x + _owner->GetRightVec() * axis.y;
			forward.Normalize();

			move += _owner->GetAirMovePower();
			
			if (_owner->GetSwitchJumpFlag())
			{
				move *= 1.0f - jumpLoopCount / 880.0f;
			}
			else
			{
				move *= 1.0f - jumpLoopCount / 560.0f;
			}

			if (move >= MaxMoveSpeed)
			{
				move = MaxMoveSpeed;
			}


			velocity.x = forward.x * move;
			velocity.y = forward.y * move;

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
			_owner->SetMoveSpeed(move);
		}
		else
		{

			move -= _owner->GetMovePower();

			if (move <= 0.0f)
			{
				move = 0.0f;
			}

			velocity.x = _owner->GetCharaForwardVec().x * move;
			velocity.y = _owner->GetCharaForwardVec().y * move;
			_owner->SetInputFlag(false);
		}
		
	}

}

void PlayerObjectStateJumpLoop::Enter(PlayerObject* _owner, float _deltaTime)
{
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	state = PlayerState::PLAYER_STATE_JUMPLOOP;
	animChangeFlag = true;
	jumpLoopCount = 0;
	velocity = _owner->GetVelocity();
	time = _deltaTime;
	if (_owner->GetNowState() == PlayerState::PLAYER_STATE_JUMPSTART)
	{
		velocity.z = _owner->GetJumpPower();
	}

	move = _owner->GetMoveSpeed();
	if (move <= 0.0f)
	{
		move = _owner->GetFirstMovePower();
	}

	inputDeadSpace = _owner->GetDeadSpace();

}
