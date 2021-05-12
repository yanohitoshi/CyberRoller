#include "PlayerObjectStateJumpStart.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateJumpStart::PlayerObjectStateJumpStart()
	: MaxFallSpeed(-2000.0f)
	, JumpCorrection(80.0f)
	, SwitchJumpCorrection(160.0f)
{
}

PlayerObjectStateJumpStart::~PlayerObjectStateJumpStart()
{
}

PlayerState PlayerObjectStateJumpStart::Update(PlayerObject* _owner, float _deltaTime)
{
	// �d�͂Ƀf���^�^�C�����������l����
	velocity.z -= PlayerObject::GetGravity() * _deltaTime;
	
	// �������x���K��l�𒴂��Ă�����
	if (velocity.z <= MaxFallSpeed)
	{
		// �K��l�ɌŒ�
		velocity.z = MaxFallSpeed;
	}

	// �ړ����x�Ƀf���^�^�C�����|���Ă�����|�W�V�����ɒǉ����čX�V
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);


	// state�I���t���O��true�ɂȂ��Ă�����
	if (endFlag == true)
	{
		// owner�ϐ����X�V
		_owner->SetMoveSpeed(moveSpeed);
		_owner->SetVelocity(velocity);
		_owner->SetJumpFrameCount(jumpFrameCount);
		// �X�e�[�^�X���W�����v���[�v�ɂ���
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

	// �ڒn�t���O��true����state�I���t���O��true�ɂȂ��Ă�����
	if (_owner->GetOnGround() == true && endFlag == true)
	{
		// owner�ϐ����X�V
		_owner->SetMoveSpeed(moveSpeed);
		_owner->SetVelocity(velocity);
		// �X�e�[�^�X�𒅒n��Ԃɂ���
		state = PlayerState::PLAYER_STATE_JUMPEND_TO_IDLE;
	}

	// ���S�t���O�������Ă�����
	if (_owner->GetDeadFlag())
	{
		state = PlayerState::PLAYER_STATE_DEAD;
	}

	// �^�C���I�[�o�[�t���O��true��������
	if (CountDownFont::timeOverFlag == true)
	{
		// �X�e�[�^�X���R���e�B�j���[�I���J�n��Ԃɂ���
		state = PlayerState::PLAYER_STATE_DOWNSTART;
	}

	// �X�V���ꂽstate��Ԃ�
	return state;
}

void PlayerObjectStateJumpStart::Input(PlayerObject* _owner, const InputState& _keyState)
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

		////���͂����邩
		if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
		{
			_owner->SetTmpCharaForwardVec(_owner->GetCharaForwardVec());

			// �����L�[�̓��͒l�ƃJ�����̌�������A�ړ�����������
			Vector3 forward = _owner->GetForwardVec() * axis.x + _owner->GetRightVec() * axis.y;
			forward.Normalize();

			// �󒆗p�̈ړ��͂̒萔�𑫂�
			moveSpeed += _owner->GetAirMovePower();

			// SwitchJump�̏ꍇ��Ԏ��Ԃ������̂Ŋ�����ύX
			if (_owner->GetSwitchJumpFlag())
			{
				// ���[�v���Ă���t���[���J�E���g��萔�Ŋ����ď��X�Ɍ�����������
				moveSpeed *= 1.0f - jumpFrameCount / SwitchJumpCorrection;
			}
			else
			{
				// ���[�v���Ă���t���[���J�E���g��萔�Ŋ����ď��X�Ɍ�����������
				moveSpeed *= 1.0f - jumpFrameCount / JumpCorrection;
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

				//��]
				Vector3 rotatioin = Vector3::Lerp(forward, tmpRotateVec, 0.01f);
				_owner->RotateToNewForward(rotatioin);
				_owner->SetRotateVec(rotatioin);

			}

			_owner->SetCharaForwardVec(forward);
			_owner->SetMoveSpeed(moveSpeed);


			_owner->SetInputFlag(true);
		}
		else
		{
			_owner->SetInputFlag(false);
		}

		if (_owner->GetIsAvailableJumpKey() == true  || _owner->GetSwitchJumpFlag() == true && _owner->GetIsAvailableJumpKey() == true)
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
					_owner->SetJumpPower(jumpPower + 100.0f);
				}
				else if (_owner->GetSwitchJumpFlag() == true && 16 > jumpFrameCount)
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
}

void PlayerObjectStateJumpStart::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPSTART),0.6f);
	// state���W�����v�J�n��Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_JUMPSTART;
	// �W�����v�t���[���J�E���g�����炤
	jumpFrameCount = _owner->GetJumpFrameCount();
	// owner�̑��x�x�N�g�������炤
	velocity = _owner->GetVelocity();
	// owner�̑��x�����炤
	moveSpeed = _owner->GetMoveSpeed();

	// �������x��0.0f�ȉ���������
	if (moveSpeed <= 0.0f)
	{
		// �����x�����炤
		moveSpeed = _owner->GetFirstMovePower();
	}

	// state�I���t���O��������
	endFlag = false;

	// ���͂�����Ȃ��l�����炤
	inputDeadSpace = _owner->GetDeadSpace();
}
