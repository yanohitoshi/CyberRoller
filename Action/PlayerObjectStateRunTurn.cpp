#include "PlayerObjectStateRunTurn.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateRunTurn::PlayerObjectStateRunTurn()
{
}

PlayerObjectStateRunTurn::~PlayerObjectStateRunTurn()
{
}

PlayerState PlayerObjectStateRunTurn::Update(PlayerObject* _owner, float _deltaTime)
{

	if (!skeletalMeshComponent->IsPlaying())
	{
		state = PlayerState::PLAYER_STATE_RUN;
	}

	return state;

}

void PlayerObjectStateRunTurn::Input(PlayerObject* _owner, const InputState& _keyState)
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


			//if (_owner->GetTmpCharaForwardVec() != _owner->GetCharaForwardVec())
			//{
			//	Vector3 tmpRotateVec = _owner->GetCharaForwardVec();
			//	tmpRotateVec.Normalize();

			//	//��]
			//	Vector3 rotatioin = Vector3::Lerp(forward, tmpRotateVec, 0.2f);
			//	_owner->RotateToNewForward(rotatioin);
			//	_owner->SetRotateVec(rotatioin);

			//}

			_owner->SetMoveSpeed(move);

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

void PlayerObjectStateRunTurn::Enter(PlayerObject* _owner, float _deltaTime)
{
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_RUN_TURN));
	state = PlayerState::PLAYER_STATE_RUN_TURN;
	move = _owner->GetMoveSpeed();

}
