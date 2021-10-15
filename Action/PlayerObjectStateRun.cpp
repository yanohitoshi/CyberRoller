//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateRun.h"
#include "SkeletalMeshComponent.h"
#include "GameObject.h"

/*
@fn �R���X�g���N�^
*/
PlayerObjectStateRun::PlayerObjectStateRun()
{
}

/*
@fn �f�X�g���N�^
*/
PlayerObjectStateRun::~PlayerObjectStateRun()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
PlayerState PlayerObjectStateRun::Update(PlayerObject* _owner,float _deltaTime)
{

	// �ړ����x�Ƀf���^�^�C�����|���Ă�����|�W�V�����ɒǉ����čX�V
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// �W�����v�t���O��false���ڒn��Ԃł��������
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
	
	// ����Ȃ���ǂɓ���������
	if (_owner->GetIsHitEnemy())
	{
		// �X�e�[�^�X�����ݏ�Ԃɂ���
		state = PlayerState::PLAYER_STATE_KNOCKBACK;
	}

	CheckDeadFlag(_owner);

	CheckTimeOverFlag();

	// owner�̕ϐ����X�V
	_owner->SetMoveSpeed(moveSpeed);
	_owner->SetVelocity(velocity);

	// �X�V���ꂽstate��Ԃ�
	return state;

}

/*
@fn �C���v�b�g
@brief	state�ɉ����ē��͏������s��
@param	_owner �e�N���X�̃|�C���^
@param	_keyState ���͏��
*/
void PlayerObjectStateRun::Input(PlayerObject* _owner,const InputState& _keyState)
{
	// ���͉\��Ԃ�������
	if (_owner->GetIsAvailableInput())
	{
		// �ړ����͏���
		GroundMove(_owner,_keyState);
	}
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void PlayerObjectStateRun::Enter(PlayerObject* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_RUN));
	// state�𑖂��Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_RUN;

	// owner�̑��x�ϐ������炤
	moveSpeed = _owner->GetMoveSpeed();

	// ���͂�����Ȃ��l�����炤
	inputDeadSpace = _owner->GetDeadSpace();
}
