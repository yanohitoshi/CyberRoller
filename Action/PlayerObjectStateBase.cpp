#include "PlayerObjectStateBase.h"
#include "CountDownFont.h"

void PlayerObjectStateBase::GroundMove(PlayerObject* _owner, const InputState& _keyState)
{
	// ���͏��`�F�b�N����
	ChackInputProcess(_owner, _keyState);
}

void PlayerObjectStateBase::ChackInput(PlayerObject* _owner, const InputState& _keyState)
{

	// �R���g���[���̃A�i���O�X�e�B�b�N�̓��͏����v�Z����
	Vector3 axis = ChackControllerAxis(_keyState);

	// �擾�������l�����ăf�b�h�X�y�[�X�O����������͏������s��
	if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
	{
		// �ړ����̓t���O��true�ɃZ�b�g
		_owner->SetInputFlag(true);
	}
	else
	{
		// �ړ����̓t���O��false�ɃZ�b�g
		_owner->SetInputFlag(false);
	}

	// �ڒn���ŃW�����v���ł��Ȃ����
	if (_owner->GetOnGround() == true && _owner->GetJumpFlag() == false)
	{
		// �W�����v�����蓖�Ă��Ă���R���g���[���[�̃{�^���������ꂽ��������̓W�����v�X�C�b�`�������ꂽ��
		if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed ||
			_owner->GetSwitchJumpFlag() == true)
		{
			// �W�����v�t���O��true�ɃZ�b�g
			_owner->SetJumpFlag(true);
		}
	}
}

void PlayerObjectStateBase::ChackDeadFlag(PlayerObject* _owner)
{
	// ���S�t���O�������Ă�����
	if (_owner->GetDeadFlag())
	{
		state = PlayerState::PLAYER_STATE_DEAD;
	}
}

void PlayerObjectStateBase::ChackTimeOverFlag()
{
	// �^�C���I�[�o�[�t���O��true��������
	if (CountDownFont::GetTimeOverFlag() == true)
	{
		// �X�e�[�^�X���R���e�B�j���[�I���J�n��Ԃɂ���
		state = PlayerState::PLAYER_STATE_DOWNSTART;
	}
}

void PlayerObjectStateBase::RotationProcess(PlayerObject* _owner, Vector3 _forward, Vector3 _tmpForward)
{
	//�O�̃t���[���ƍ��̃t���[���̑O���x�N�g���Ő��`��Ԃ����
	Vector3 rotatioin = Vector3::Lerp(_forward, _tmpForward, 0.01f);

	// ��]�������߂�
	_owner->RotateToNewForward(rotatioin);
	// �O���x�N�g���X�V
	_owner->SetCharaForwardVec(rotatioin);
}

Vector3 PlayerObjectStateBase::ChackControllerAxis(const InputState& _keyState)
{
	//Axis�̒l���Ƃ�32700~-32700
	float ALX = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTX);
	float ALY = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTY);

	//�A�i���O�X�e�B�b�N�̃L�[���͂��擾
	Vector2 Axis = Vector2(0.0f, 0.0f);
	Axis = _keyState.Controller.GetLAxisLeftVec();

	//���ۂɓ�����������������Ă���̂ŕ␳
	Vector3 axis = Vector3(Axis.y * -1.0f, Axis.x * -1.0f, 0.0f);

	// ����Ԃ�
	return axis;
}

void PlayerObjectStateBase::ChackInputProcess(PlayerObject* _owner, const InputState& _keyState)
{
	// �R���g���[���̃A�i���O�X�e�B�b�N�̓��͏����v�Z����
	Vector3 axis = ChackControllerAxis(_keyState);

	// �擾�������l�����ăf�b�h�X�y�[�X�O����������͏������s��
	if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
	{
		// ���͂�����ꍇ�̏���
		InputMovableProcess(_owner, axis);
	}
	else
	{
		// ���͂��Ȃ��ꍇ�̏���
		UninputMovableProcess(_owner);
	}

	// �W�����v�����蓖�Ă��Ă���R���g���[���[�̃{�^���������ꂽ��������̓W�����v�X�C�b�`�������ꂽ��
	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed ||
		_owner->GetSwitchJumpFlag() == true)
	{
		// �W�����v��ԑJ�ڏ���
		JumpTransitionProcess(_owner);
	}
}

void PlayerObjectStateBase::InputMovableProcess(PlayerObject* _owner, Vector3 _axis)
{
	// �O�̃t���[���̃L�����N�^�[�̑O���x�N�g����ۑ�
	Vector3 tmpForward = _owner->GetCharaForwardVec();

	// �����L�[�̓��͒l�ƃJ�����̌�������A�ړ�����������
	Vector3 forward = _owner->GetForwardVec() * _axis.x + _owner->GetRightVec() * _axis.y;

	if (!Math::NearZero(forward.Length()))
	{
		forward.Normalize();
	}

	// �ړ����x�ɉ����x�𑫂�
	moveSpeed += _owner->GetMovePower();

	// �ړ����x���ő�l�𒴂��Ă�����Œ肷��
	if (moveSpeed >= MaxMoveSpeed)
	{
		// �ړ����x�̍ő�萔����
		moveSpeed = MaxMoveSpeed;
	}

	Vector2 absAxis = Vector2(fabs(_axis.x), fabs(_axis.y));

	// �ړ��x�N�g���ɑ��x��������
	if (absAxis.x > absAxis.y)
	{
		moveSpeed *= absAxis.x;
	}
	else
	{
		moveSpeed *= absAxis.y;
	}

	velocity.x = forward.x * moveSpeed;
	velocity.y = forward.y * moveSpeed;


	// ��]����
	RotationProcess(_owner, forward, tmpForward);

	// owner�̈ړ����x���X�V
	_owner->SetMoveSpeed(moveSpeed);
}

void PlayerObjectStateBase::InputJumpMovableProcess(PlayerObject* _owner, Vector3 _axis)
{
	// �O�̃t���[���̃L�����N�^�[�̑O���x�N�g����ۑ�
	Vector3 tmpForward = _owner->GetCharaForwardVec();

	// �����L�[�̓��͒l�ƃJ�����̌�������A�ړ�����������
	Vector3 forward = _owner->GetForwardVec() * _axis.x + _owner->GetRightVec() * _axis.y;
	forward.Normalize();

	// �󒆗p�̈ړ��͂̒萔�𑫂�
	moveSpeed += _owner->GetAirMovePower();

	// �ړ����x���ő呬�x�𒴂��Ă�����
	if (moveSpeed >= MaxMoveSpeed)
	{
		// �ō����x�ɌŒ肷��
		moveSpeed = MaxMoveSpeed;
	}

	// �A�i���O�X�e�B�b�N�̓��͊p�x���Βl��
	Vector2 absAxis = Vector2(fabs(_axis.x), fabs(_axis.y));
	// �A�i���O�X�e�B�b�N�̓��͂��l�������ړ����x�̍쐬
	if (absAxis.x > absAxis.y)
	{
		moveSpeed *= absAxis.x;
	}
	else
	{
		moveSpeed *= absAxis.y;
	}

	// X����Y���ɑO���x�N�g���ɑ��x�������đ��x�t���x�N�g�������
	velocity.x = forward.x * moveSpeed;
	velocity.y = forward.y * moveSpeed;

	// ��]����
	RotationProcess(_owner, forward, tmpForward);

	// owner�̑��x�ϐ����X�V
	_owner->SetMoveSpeed(moveSpeed);
}

void PlayerObjectStateBase::UninputMovableProcess(PlayerObject* _owner)
{
	// �ړ����̓t���O��false�ɃZ�b�g
	_owner->SetInputFlag(false);
}

void PlayerObjectStateBase::JumpTransitionProcess(PlayerObject* _owner)
{
	// �W�����v�t���O��true�ɃZ�b�g
	_owner->SetJumpFlag(true);
}
