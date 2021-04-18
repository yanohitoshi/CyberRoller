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

	if (_owner->GetOnGround() == true && _owner->GetInputFlag() && moveSpeed >= 600.0f)
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
	_owner->SetMoveSpeed(moveSpeed);

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

			// 空中用の移動力の定数を足す
			moveSpeed += _owner->GetAirMovePower();
			
			// SwitchJumpの場合飛ぶ時間が長いので割合を変更
			if (_owner->GetSwitchJumpFlag())
			{
				// ループしているフレームカウントを割って一定数ずつ減速をかける
				moveSpeed *= 1.0f - jumpLoopCount / 1320.0f;
			}
			else
			{
				// ループしているフレームカウントを割って一定数ずつ減速をかける
				moveSpeed *= 1.0f - jumpLoopCount / 840.0f;
			}

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

			moveSpeed -= _owner->GetAirMovePower();

			if (moveSpeed <= 0.0f)
			{
				moveSpeed = 0.0f;
			}

			velocity.x = _owner->GetCharaForwardVec().x * moveSpeed;
			velocity.y = _owner->GetCharaForwardVec().y * moveSpeed;
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
	if (_owner->GetNowState() == PlayerState::PLAYER_STATE_JUMPSTART)
	{
		velocity.z = _owner->GetJumpPower();
	}

	moveSpeed = _owner->GetMoveSpeed();

	if (moveSpeed <= 0.0f)
	{
		moveSpeed = _owner->GetFirstMovePower();
	}

	inputDeadSpace = _owner->GetDeadSpace();

}
