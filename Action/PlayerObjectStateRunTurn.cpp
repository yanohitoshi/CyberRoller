#include "PlayerObjectStateRunTurn.h"
#include "SkeletalMeshComponent.h"
#include "CountDownFont.h"

PlayerObjectStateRunTurn::PlayerObjectStateRunTurn()
{
}

PlayerObjectStateRunTurn::~PlayerObjectStateRunTurn()
{
}

PlayerState PlayerObjectStateRunTurn::Update(PlayerObject* _owner, float _deltaTime)
{

	if (move >= 0.0f)
	{
		move -= 80.0f;
	}

	velocity.x = _owner->GetCharaForwardVec().x * move * -1.0f;
	velocity.y = _owner->GetCharaForwardVec().y * move * -1.0f;

	// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	if (!skeletalMeshComponent->IsPlaying())
	{
		state = PlayerState::PLAYER_STATE_RUN;
		if (move <= 200.0f)
		{
			move = 200.0f;
		}
	}

	if (!_owner->GetInputFlag())
	{
		state = PlayerState::PLAYER_STATE_RUN_STOP;
	}

	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

	if (_owner->GetIsJumping() || _owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		state = PlayerState::PLAYER_STATE_JUMPSTART;
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
	_owner->SetMoveSpeed(move);

	// �X�V���ꂽstate��Ԃ�
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
		if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
		{
			_owner->SetTmpCharaForwardVec(_owner->GetCharaForwardVec());

			// �����L�[�̓��͒l�ƃJ�����̌�������A�ړ�����������
			Vector3 forward = _owner->GetForwardVec() * axis.x + _owner->GetRightVec() * axis.y;
			forward.Normalize();
			_owner->SetCharaForwardVec(forward);

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

void PlayerObjectStateRunTurn::Enter(PlayerObject* _owner, float _deltaTime)
{
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_RUN_TURN),1.5f);
	state = PlayerState::PLAYER_STATE_RUN_TURN;
	move = _owner->GetMoveSpeed();

	inputDeadSpace = _owner->GetDeadSpace();
	_owner->SetTurnDelayCount(0);
}
