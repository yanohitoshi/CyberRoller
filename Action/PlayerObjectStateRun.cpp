#include "PlayerObjectStateRun.h"
#include "SkeletalMeshComponent.h"
#include "GameObject.h"

PlayerObjectStateRun::PlayerObjectStateRun()
{
}

PlayerObjectStateRun::~PlayerObjectStateRun()
{
}

PlayerState PlayerObjectStateRun::Update(PlayerObject* _owner,float _deltaTime)
{

	_owner->SetVelocity(velocity);
	// positionに速度を足してキャラクターを動かす
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

	if (!_owner->GetInputFlag())
	{
		state = PlayerState::PLAYER_STATE_IDLE;
	}

	if (_owner->GetIsJumping() || _owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	if (_owner->GetDeadFlag())
	{
		state = PlayerState::PLAYER_STATE_DEAD;
	}

	return state;

}

void PlayerObjectStateRun::Input(PlayerObject* _owner,const InputState& _keyState)
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
		else
		{
			_owner->SetInputFlag(false);
		}

		if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed)
		{
			//jumpFlag = true;
			_owner->SetJumpFlag(true);
			//isJumping = true;
			_owner->SetIsJumping(true);
		}

	}



}

void PlayerObjectStateRun::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_RUN));
	state = PlayerState::PLAYER_STATE_RUN;
}
