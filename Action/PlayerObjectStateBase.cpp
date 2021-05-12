#include "PlayerObjectStateBase.h"

void PlayerObjectStateBase::GroundMove(PlayerObject* _owner, const InputState& _keyState)
{

	////Axis�̒l���Ƃ�32700~-32700
	//float ALX = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTX);
	//float ALY = _keyState.Controller.GetAxisValue(SDL_CONTROLLER_AXIS_LEFTY);

	////�A�i���O�X�e�B�b�N�̃L�[���͂��擾
	//Vector2 Axis = Vector2(0.0f, 0.0f);
	//Axis = _keyState.Controller.GetLAxisLeftVec();

	//���ۂɓ�����������������Ă���̂ŕ␳
	Vector3 axis = ChackControllerAxis(_keyState);

	//���͂����邩
	if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
	{
		_owner->SetTmpCharaForwardVec(_owner->GetCharaForwardVec());

		// �����L�[�̓��͒l�ƃJ�����̌�������A�ړ�����������
		Vector3 forward = _owner->GetForwardVec() * axis.x + _owner->GetRightVec() * axis.y;
		forward.Normalize();


		moveSpeed += _owner->GetMovePower();

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
		_owner->SetJumpFlag(true);
		_owner->SetIsJumping(true);
	}

}

void PlayerObjectStateBase::ChackInput(PlayerObject* _owner, const InputState& _keyState)
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
	if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
	{
		_owner->SetInputFlag(true);
	}
	else
	{
		_owner->SetInputFlag(false);
	}

	if (_owner->GetOnGround() == true && _owner->GetJumpFlag() == false)
	{
		if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
			_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed ||
			_owner->GetSwitchJumpFlag() == true)
		{
			_owner->SetJumpFlag(true);
			_owner->SetIsJumping(true);
		}
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

	return axis;
}
