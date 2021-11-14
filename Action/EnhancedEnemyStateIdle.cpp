#include "EnhancedEnemyStateIdle.h"

EnhancedEnemyStateIdle::EnhancedEnemyStateIdle()
	: StayTime(40)
{
}

EnhancedEnemyStateIdle::~EnhancedEnemyStateIdle()
{

}

EnemyState EnhancedEnemyStateIdle::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	++frameCount;
	if (_owner->GetIsTracking() && !_owner->GetIsDead() && frameCount > StayTime)
	{
		state = EnemyState::ENEMY_STATE_TRACKING;
	}

	if (_owner->GetIsDead())
	{
		state = EnemyState::ENEMY_STATE_DEAD;
	}

	return state;
}

void EnhancedEnemyStateIdle::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// �Đ�����A�j���[�V���������炢�Đ���������
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// state��ҋ@��Ԃɂ��ĕۑ�
	state = EnemyState::ENEMY_STATE_IDLE;
	_owner->SetState(State::Active);
	frameCount = 0;
}
