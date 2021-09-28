#include "TrackingEnemyStateDead.h"

TrackingEnemyStateDead::TrackingEnemyStateDead()
{
}

TrackingEnemyStateDead::~TrackingEnemyStateDead()
{
}

EnemyState TrackingEnemyStateDead::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	++frameCount;

	if (frameCount >= 120)
	{
		skeletalMeshComponent->SetVisible(false);
		state = EnemyState::ENEMY_STATE_RESPAWN;
	}

	return state;
}

void TrackingEnemyStateDead::Enter(EnemyObjectBase* _owner, float _deltaTime)
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
