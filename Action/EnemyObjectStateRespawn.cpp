#include "EnemyObjectStateRespawn.h"

EnemyObjectStateRespawn::EnemyObjectStateRespawn()
	: nowScale(Vector3::Zero)
{
}

EnemyObjectStateRespawn::~EnemyObjectStateRespawn()
{
}

EnemyState EnemyObjectStateRespawn::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	nowScale += Vector3(0.01f, 0.01f, 0.01f);
	_owner->SetScale(nowScale);

	if (nowScale.x >= 2.0f)
	{
		_owner->SetScale(Vector3(2.0f, 2.0f, 2.0f));
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
	_owner->SetScale(Vector3::Zero);
	// ���݂�scale�l���擾
	nowScale = Vector3::Zero;
	// ���S�t���O��false�ɃZ�b�g
	_owner->SetIsDeadFlag(false);
	// position�������ʒu�ɒ���
	_owner->SetPosition(_owner->GetFirstPosition());
}
