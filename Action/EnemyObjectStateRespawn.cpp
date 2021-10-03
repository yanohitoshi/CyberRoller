#include "EnemyObjectStateRespawn.h"

EnemyObjectStateRespawn::EnemyObjectStateRespawn()
	: moveDirection(Vector3::Zero)
	, nowPosition(Vector3::Zero)
	, RespawnMoveSpeed(200.0f)
{
}

EnemyObjectStateRespawn::~EnemyObjectStateRespawn()
{
}

EnemyState EnemyObjectStateRespawn::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	nowPosition = _owner->GetPosition();
	moveDirection = _owner->GetFirstPosition() - nowPosition;
	moveDirection.Normalize();
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
	// position�����X�|�[������ꏊ�ɃZ�b�g
	_owner->SetPosition(_owner->GetRespawnPosition());
}