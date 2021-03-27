#include "PlayerObjectStateJumpLoop.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateJumpLoop::PlayerObjectStateJumpLoop()
{
}

PlayerObjectStateJumpLoop::~PlayerObjectStateJumpLoop()
{
}

PlayerState PlayerObjectStateJumpLoop::Update(PlayerObject* _owner, float _deltaTime)
{
	velocity.z -= PlayerObject::GetGravity() * _deltaTime;
	if (velocity.z <= -2000.0f)
	{
		velocity.z = -2000.0f;
	}

	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	if (_owner->GetOnGround() == true && state == PlayerState::PLAYER_STATE_JUMPLOOP)
	{
		state = PlayerState::PLAYER_STATE_JUMPEND;
	}

	return state;
}

void PlayerObjectStateJumpLoop::Input(PlayerObject* _owner, const InputState& _keyState)
{
	
	//Axis�̒l���Ƃ�32700~-32700
	float ALX = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTX);
	float ALY = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTY);

	//�A�i���O�X�e�B�b�N�̃L�[���͂��擾
	Vector2 Axis = Vector2(0.0f, 0.0f);
	Axis = _keyState.Controller.GetLAxisLeftVec();

	//���ۂɓ�����������������Ă���̂ŕ␳
	Vector3 axis = Vector3(Axis.y * -1.0f, Axis.x * -1.0f, 0.0f);

	//���͂����邩
	if (Math::Abs(axis.x) > 0.0f || Math::Abs(axis.y) > 0.0f)
	{
		// �����L�[�̓��͒l�ƃJ�����̌�������A�ړ�����������
		// charaForwardVec = forwardVec * axis.x + rightVec * axis.y;
		Vector3 tmpVec = _owner->GetForwardVec() * axis.x + _owner->GetRightVec() * axis.y;
		tmpVec.Normalize();
		_owner->SetCharaForwardVec(tmpVec);
		// inputFlag = true;

		velocity.x = _owner->GetCharaForwardVec().x * _owner->GetMoveSpeed() * 2.0f;
		velocity.y = _owner->GetCharaForwardVec().y * _owner->GetMoveSpeed() * 2.0f;


		if (_owner->GetTmpCharaForwardVec() != _owner->GetCharaForwardVec())
		{
			Vector3 tmpRotateVec = _owner->GetCharaForwardVec();
			tmpRotateVec.Normalize();
			//��]
			_owner->SetRotateVec(Vector3::Lerp(_owner->GetRotateVec(), tmpRotateVec, 0.2f));
			//RotateToNewForward(rotateVec);
		}
	}

	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Released ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Released ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Released ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Released )
	{
		//isAvailableJumpKey = false;
		_owner->SetIsAvailableJumpKey(false);
		//isJumping = false;
		_owner->SetIsJumping(false);
		//jumpPower = FirstJumpPower;
		_owner->SetJumpPower(_owner->GetFirstJumpPower());
	}


	if (_owner->GetIsAvailableJumpKey() == true && _owner->GetIsJumping()  == true || _owner->GetSwitchJumpFlag() == true && _owner->GetIsAvailableJumpKey() == true)
	{
		if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Held ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Held ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Held ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Held ||
			_owner->GetSwitchJumpFlag() == true)
		{
			++jumpFrameCount;
			//jumpFlag = true;
			_owner->SetJumpFlag(true);
			velocity.z = _owner->GetJumpPower();

			if (jumpFrameCount > 0 && jumpFrameCount < 12 && _owner->GetSwitchJumpFlag() == false)
			{
				_owner->SetJumpPower( _owner->GetJumpPower() + 100.0f);
			}
			else if (_owner->GetSwitchJumpFlag() == true && jumpFrameCount < 14)
			{
				_owner->SetJumpPower(_owner->GetJumpPower() + 150.0f);
				//jumpPower += 150.0f;
			}
			else
			{
				//isAvailableJumpKey = false;
				_owner->SetIsAvailableJumpKey(false);
				//isJumping = false;
				_owner->SetIsJumping(false);
				//switchJumpFlag = false;
				_owner->SetSwitchJumpFlag(false);
			}
		}
	}
}

void PlayerObjectStateJumpLoop::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPLOOP));
	jumpFrameCount = _owner->GetJumpFrameCount();
	velocity = _owner->GetVelocity();
	state = PlayerState::PLAYER_STATE_JUMPLOOP;
}
