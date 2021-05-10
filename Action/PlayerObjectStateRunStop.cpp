#include "PlayerObjectStateRunStop.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateRunStop::PlayerObjectStateRunStop()
{
}

PlayerObjectStateRunStop::~PlayerObjectStateRunStop()
{
}

PlayerState PlayerObjectStateRunStop::Update(PlayerObject* _owner, float _deltaTime)
{

	++isTurnCount;

	if (moveSpeed >= 0.0f)
	{
		moveSpeed -= decelerationForce;
	}

	velocity.x = _owner->GetCharaForwardVec().x * moveSpeed;
	velocity.y = _owner->GetCharaForwardVec().y * moveSpeed;

	// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);


	if (!skeletalMeshComponent->IsPlaying() || moveSpeed <= 0.0f)
	{
		state = PlayerState::PLAYER_STATE_IDLE;
	}

	if (_owner->GetInputFlag() && _owner->GetTurnDelayCount() >= 30 && isTurnCount <= 10)
	{
		state = PlayerState::PLAYER_STATE_RUN_TURN;
	}

	if (_owner->GetIsJumping() || _owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

	_owner->SetVelocity(velocity);

	// �X�V���ꂽstate��Ԃ�
	return state;
}

void PlayerObjectStateRunStop::Input(PlayerObject* _owner, const InputState& _keyState)
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
			_owner->SetInputFlag(true);
			//�A�i���O�X�e�B�b�N�̓��͏�Ԃő����Ԃ�����
			if (ALX >= 28000.0f || ALX <= -28000.0f || ALY >= 28000.0f || ALY <= -28000.0f)
			{
				_owner->SetRunFlag(true);
			}
			else
			{
				_owner->SetRunFlag(false);
			}
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

}

void PlayerObjectStateRunStop::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_RUN_STOP));
	// state�𑖂�I����Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_RUN_STOP;
	moveSpeed = _owner->GetMoveSpeed();

	inputDeadSpace = _owner->GetDeadSpace();
	isTurnCount = 0;
	decelerationForce = _owner->GetDecelerationForce();
}
