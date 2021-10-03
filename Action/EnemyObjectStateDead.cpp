#include "EnemyObjectStateDead.h"

EnemyObjectStateDead::EnemyObjectStateDead()
	: RespawnTime(120)
{
}

EnemyObjectStateDead::~EnemyObjectStateDead()
{
}

EnemyState EnemyObjectStateDead::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	++frameCount;

	// ���Ԃ������烊�X�|�[��
	if (frameCount >= RespawnTime)
	{
		skeletalMeshComponent->SetVisible(false);
		state = EnemyState::ENEMY_STATE_RESPAWN;
	}

	return state;
}

void EnemyObjectStateDead::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_DEAD));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_DEAD;

	_owner->SetState(State::Disabling);
	frameCount = 0;
}
