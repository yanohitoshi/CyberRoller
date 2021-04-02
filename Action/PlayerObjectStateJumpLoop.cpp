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

	//if (!_owner->GetInputFlag())
	//{
	//	move -= 100.0f;
	//	if (move <= 0.0f)
	//	{
	//		move = 0.0f;
	//	}
	//}

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

	if (_owner->GetOnGround() == true)
	{
		_owner->SetVelocity(velocity);
		_owner->SetMoveSpeed(move);
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
		if (Math::Abs(axis.x) > 0.0f || Math::Abs(axis.y) > 0.0f)
		{
			_owner->SetTmpCharaForwardVec(_owner->GetCharaForwardVec());
			// 方向キーの入力値とカメラの向きから、移動方向を決定
			Vector3 forward = _owner->GetForwardVec() * axis.x + _owner->GetRightVec() * axis.y;
			forward.Normalize();
			_owner->SetCharaForwardVec(forward);

			move += _owner->GetMovePower();

			if (move >= 1600.0f)
			{
				move = 1600.0f;
			}

			velocity.x = _owner->GetCharaForwardVec().x * move;
			velocity.y = _owner->GetCharaForwardVec().y * move;


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
	}

}

void PlayerObjectStateJumpLoop::Enter(PlayerObject* _owner, float _deltaTime)
{
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	state = PlayerState::PLAYER_STATE_JUMPLOOP;
	animChangeFlag = true;
	jumpFrameCount = _owner->GetJumpFrameCount();
	velocity = _owner->GetVelocity();

	if (_owner->GetNowState() == PlayerState::PLAYER_STATE_JUMPSTART)
	{
		velocity.z = _owner->GetJumpPower();
	}

	move = _owner->GetMoveSpeed();
	if (move <= 0.0f)
	{
		move = _owner->GetFirstMovePower();
	}

}
