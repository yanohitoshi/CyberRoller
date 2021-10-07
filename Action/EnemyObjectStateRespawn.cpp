//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectStateRespawn.h"

/*
@fn �R���X�g���N�^
*/
EnemyObjectStateRespawn::EnemyObjectStateRespawn()
	: moveDirection(Vector3::Zero)
	, nowPosition(Vector3::Zero)
	, RespawnMoveSpeed(200.0f)
{
}

/*
@fn �f�X�g���N�^
*/
EnemyObjectStateRespawn::~EnemyObjectStateRespawn()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
EnemyState EnemyObjectStateRespawn::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// �I�[�i�[�̍��̃|�W�V�������擾
	nowPosition = _owner->GetPosition();
	// ���̃|�W�V�������珉���|�W�V�����֌����������x�N�g�����쐬
	moveDirection = _owner->GetFirstPosition() - nowPosition;
	// ���K��
	moveDirection.Normalize();
	// ���x���v�Z��
	velocity = moveDirection * RespawnMoveSpeed;
	// position�ɑ��x�𑫂��ăL�����N�^�[�𓮂���
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	// ���݂̃|�W�V�����������|�W�V�����ȉ��ɂȂ�����
	// ���ォ��~��Ă��邽��
	if (nowPosition.z <= _owner->GetFirstPosition().z)
	{
		state = EnemyState::ENEMY_STATE_IDLE;
	}

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void EnemyObjectStateRespawn::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// �`���ON�ɐݒ�
	skeletalMeshComponent->SetVisible(true);
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_RESPAWN;
	// ���S�t���O��false�ɃZ�b�g
	_owner->SetIsDeadFlag(false);
	_owner->SetIsAttack(false);
	// position�����X�|�[������ꏊ�ɃZ�b�g
	_owner->SetPosition(_owner->GetRespawnPosition());
}