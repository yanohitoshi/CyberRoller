//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateRunTurn.h"
#include "SkeletalMeshComponent.h"

/*
@fn �R���X�g���N�^
*/
PlayerObjectStateRunTurn::PlayerObjectStateRunTurn()
	: MinimumSpeed(200.0f)
{
}

/*
@fn �f�X�g���N�^
*/
PlayerObjectStateRunTurn::~PlayerObjectStateRunTurn()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
*/
PlayerState PlayerObjectStateRunTurn::Update(PlayerObject* _owner, float _deltaTime)
{
	// ���x��0.0f�ȏゾ������
	if (moveSpeed >= 0.0f)
	{
		// ������������
		moveSpeed -= decelerationForce;
	}

	// �L�����N�^�[�̑O���x�N�g���Ɉړ����x�������ă^�[������̂�-1.0f��������
	velocity.x = _owner->GetCharaForwardVec().x * moveSpeed * -1.0f;
	velocity.y = _owner->GetCharaForwardVec().y * moveSpeed * -1.0f;

	// �ړ����x�Ƀf���^�^�C�����|���Ă�����|�W�V�����ɒǉ����čX�V
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// �A�j���[�V�����̍Đ����I����Ă�����
	if (!skeletalMeshComponent->IsPlaying())
	{
		// �X�e�[�^�X�𑖂��Ԃɂ���
		state = PlayerState::PLAYER_STATE_RUN;
		// ���x���K��l�ȉ���������
		if (moveSpeed <= MinimumSpeed)
		{
			// ���x���K��l�ɂ���
			moveSpeed = MinimumSpeed;
		}
	}

	// �ړ����͂��������
	if (!_owner->GetInputFlag())
	{
		// �X�e�[�^�X�𑖂�I���ɂ���
		state = PlayerState::PLAYER_STATE_RUN_STOP;
	}

	// �W�����v�t���O��false�Őڒn��Ԃł��������
	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		// �X�e�[�^�X���W�����v���[�v�ɂ���
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

	// �W�����v�t���O�������̓X�C�b�`�W�����v�t���O��true��������
	if (_owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		// �X�e�[�^�X���W�����v�J�n��Ԃɂ���
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	// ���S��ԃ`�F�b�N
	CheckDeadFlag(_owner);

	// ���Ԑ؂�`�F�b�N
	CheckTimeOverFlag();

	// owner�̕ϐ����X�V
	_owner->SetVelocity(velocity);
	_owner->SetMoveSpeed(moveSpeed);

	// �X�V���ꂽstate��Ԃ�
	return state;
}

/*
@fn �C���v�b�g
@brief	state�ɉ����ē��͏������s��
@param	_owner �e�N���X�̃|�C���^
@param	_keyState ���͏��
*/
void PlayerObjectStateRunTurn::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// ���͉\��Ԃ�������
	if (_owner->GetIsAvailableInput())
	{
		// ���͏��`�F�b�N����
		CheckInputProcess(_owner, _keyState);
	}
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void PlayerObjectStateRunTurn::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_RUN_TURN),1.5f);
	// state��؂�ւ�����Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_RUN_TURN;
	// owner�̑��x�����炤
	moveSpeed = _owner->GetMoveSpeed();
	// �����x�����炤
	decelerationForce = _owner->GetDecelerationForce();
	// ���͂�����Ȃ��l�����炤
	inputDeadSpace = _owner->GetDeadSpace();
	// owner�̃^�[���Ԋu���x��������
	_owner->SetTurnDelayCount(0);
}

/*
@fn ���̓`�F�b�N�֐������֐�
@param	_owner �e�N���X�̃|�C���^
@param	_keyState ���͏��
*/
void PlayerObjectStateRunTurn::CheckInputProcess(PlayerObject* _owner, const InputState& _keyState)
{
	// �R���g���[���̃A�i���O�X�e�B�b�N�̓��͏����v�Z����
	Vector3 axis = CheckControllerAxis(_keyState);

	// �擾�������l�����ăf�b�h�X�y�[�X�O����������͏������s��
	if (Math::Abs(axis.x) > inputDeadSpace || Math::Abs(axis.y) > inputDeadSpace)
	{
		// ���͂�����ꍇ�̏���
		InputMovableProcess(_owner,axis);
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
		// �W�����v����
		JumpTransitionProcess(_owner);
	}
}

/*
@fn ���͂�����ꍇ�̏����֐�
@param	_owner �e�N���X�̃|�C���^
@param	_axis �␳�ς݂̃A�i���O�X�e�B�b�N���
*/
void PlayerObjectStateRunTurn::InputMovableProcess(PlayerObject* _owner, Vector3 _axis)
{
	// �����L�[�̓��͒l�ƃJ�����̌�������A�ړ�����������
	Vector3 forward = _owner->GetForwardVec() * _axis.x + _owner->GetRightVec() * _axis.y;

	if (!Math::NearZero(forward.Length()))
	{
		// �x�N�g���̐��K��
		forward.Normalize();
	}
	// �O���x�N�g���̍X�V
	_owner->SetCharaForwardVec(forward);
	// ���̓t���O��true��
	_owner->SetInputFlag(true);
}

/*
@fn ���͂��Ȃ��ꍇ�̏����֐�
@param	_owner �e�N���X�̃|�C���^
*/
void PlayerObjectStateRunTurn::UninputMovableProcess(PlayerObject* _owner)
{
	// ���̓t���O��false��
	_owner->SetInputFlag(false);
}

/*
@fn �W�����v��ԂɑJ�ڂ��邽�߂̏��������֐�
@param	_owner �e�N���X�̃|�C���^
*/
void PlayerObjectStateRunTurn::JumpTransitionProcess(PlayerObject* _owner)
{
	// �W�����v�t���O��true�ɃZ�b�g
	_owner->SetJumpFlag(true);
}
