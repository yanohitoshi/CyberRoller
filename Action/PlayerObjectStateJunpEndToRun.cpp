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

	// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
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

	return state;
}

void PlayerObjectStateJunpEndToRun::Input(PlayerObject* _owner, const InputState& _keyState)
{
	if (_owner->GetIsAvailableInput())
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
		if (Math::Abs(axis.x) > 0.3f || Math::Abs(axis.y) > 0.3f)
		{
			_owner->SetTmpCharaForwardVec(_owner->GetCharaForwardVec());

			// �����L�[�̓��͒l�ƃJ�����̌�������A�ړ�����������
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

				//��]
				Vector3 rotatioin = Vector3::Lerp(forward, tmpRotateVec, 0.2f);
				_owner->RotateToNewForward(rotatioin);
				_owner->SetRotateVec(rotatioin);

			}

			//_owner->SetMoveSpeed(move);

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

		_owner->SetMoveSpeed(move);

	}
}

void PlayerObjectStateJunpEndToRun::Enter(PlayerObject* _owner, float _deltaTime)
{
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPEND_TO_RUN));
	state = PlayerState::PLAYER_STATE_JUMPEND_TO_RUN;

	_owner->SetJumpPower(_owner->GetFirstJumpPower());
	//velocity = _owner->GetVelocity();
	endFlag = false;
}
