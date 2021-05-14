#include "PlayerObjectStateBase.h"

void PlayerObjectStateBase::GroundMove(PlayerObject* _owner, const InputState& _keyState)
{
	// �R���g���[���̃A�i���O�X�e�B�b�N�̓��͏����v�Z����
	Vector3 axis = ChackControllerAxis(_keyState);

	// �擾�������l�����ăf�b�h�X�y�[�X�O����������͏������s��
	if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
	{
		// �O�̃t���[���̃L�����N�^�[�̑O���x�N�g����ۑ�
		Vector3 tmpForward = _owner->GetCharaForwardVec();

		// �����L�[�̓��͒l�ƃJ�����̌�������A�ړ�����������
		Vector3 forward = _owner->GetForwardVec() * axis.x + _owner->GetRightVec() * axis.y;
		forward.Normalize();

		// �ړ����x�ɉ����x�𑫂�
		moveSpeed += _owner->GetMovePower();

		// �ړ����x���ő�l�𒴂��Ă�����Œ肷��
		if (moveSpeed >= MaxMoveSpeed)
		{
			// �ړ����x�̍ő�萔����
			moveSpeed = MaxMoveSpeed;
		}

		// �ړ��x�N�g���ɑ��x��������
		velocity.x = forward.x * moveSpeed;
		velocity.y = forward.y * moveSpeed;

		// ��]����
		RotationProcess(_owner, forward, tmpForward);

		// owner�̈ړ����x���X�V
		_owner->SetMoveSpeed(moveSpeed);

	}
	else
	{
		// �ړ����̓t���O��false�ɃZ�b�g
		_owner->SetInputFlag(false);
	}

	// �W�����v�����蓖�Ă��Ă���R���g���[���[�̃{�^���������ꂽ��
	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed)
	{
		// �W�����v�t���O��true�ɃZ�b�g
		_owner->SetJumpFlag(true);
	}

}

void PlayerObjectStateBase::ChackInput(PlayerObject* _owner, const InputState& _keyState)
{

	// �R���g���[���̃A�i���O�X�e�B�b�N�̓��͏����v�Z����
	Vector3 axis = ChackControllerAxis(_keyState);

	// �擾�������l�����ăf�b�h�X�y�[�X�O����������͏������s��
	if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
	{
		// 
		_owner->SetInputFlag(true);
	}
	else
	{
		_owner->SetInputFlag(false);
	}

	// �ڒn���ŃW�����v���ł��Ȃ����
	if (_owner->GetOnGround() == true && _owner->GetJumpFlag() == false)
	{
		// �W�����v�����蓖�Ă��Ă���R���g���[���[�̃{�^���������ꂽ��
		if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed ||
			_owner->GetSwitchJumpFlag() == true)
		{
			_owner->SetJumpFlag(true);
		}
	}
}

void PlayerObjectStateBase::RotationProcess(PlayerObject* _owner, Vector3 _forward, Vector3 _tmpForward)
{
	// �O���x�N�g�����O�̃t���[������ς���Ă�����
	if (_tmpForward != _forward)
	{
		//�O�̃t���[���ƍ��̃t���[���̑O���x�N�g���Ő��`��Ԃ����
		Vector3 rotatioin = Vector3::Lerp(_forward, _tmpForward, 0.01f);

		// ��]�������߂�
		_owner->RotateToNewForward(rotatioin);
		// �O���x�N�g���X�V
		_owner->SetCharaForwardVec(rotatioin);
	}

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
