//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateRunStart.h"
#include "SkeletalMeshComponent.h"

/*
@fn �R���X�g���N�^
*/
PlayerObjectStateRunStart::PlayerObjectStateRunStart()
{
}

/*
@fn �f�X�g���N�^
*/
PlayerObjectStateRunStart::~PlayerObjectStateRunStart()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
PlayerState PlayerObjectStateRunStart::Update(PlayerObject* _owner, float _deltaTime)
{
	// �ړ����x�Ƀf���^�^�C�����|���Ă�����|�W�V�����ɒǉ����čX�V
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// �A�j���[�V�����̍Đ����I����Ă�����
	if (!skeletalMeshComponent->IsPlaying())
	{
		// �X�e�[�^�X�𑖂��Ԃɂ���
		state = PlayerState::PLAYER_STATE_RUN;
	}

	// �W�����v�t���O��false�Őڒn��Ԃł��������
	if (!_owner->GetJumpFlag() && !_owner->GetOnGround())
	{
		// �X�e�[�^�X���W�����v���[�v�ɂ���
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}
	// �ړ����͂��������
	if (!_owner->GetInputFlag())
	{
		// �X�e�[�^�X�𑖂�I���ɂ���
		state = PlayerState::PLAYER_STATE_RUN_STOP;
	}
	// �W�����v�t���O�������̓X�C�b�`�W�����v�t���O��true��������
	if (_owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		// �X�e�[�^�X���W�����v�J�n��Ԃɂ���
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	CheckDeadFlag(_owner);

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
void PlayerObjectStateRunStart::Input(PlayerObject* _owner, const InputState& _keyState)
{
	// ���͉\��Ԃ�������
	if (_owner->GetIsAvailableInput())
	{
		// �ړ����͏���
		GroundMove(_owner, _keyState);
	}
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void PlayerObjectStateRunStart::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_RUN_START));
	// state�𑖂�o����Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_RUN_START;
	// owner�̈ړ����x�����炤
	moveSpeed = _owner->GetMoveSpeed();

	// ���͂�����Ȃ��l�����炤
	inputDeadSpace = _owner->GetDeadSpace();
}
