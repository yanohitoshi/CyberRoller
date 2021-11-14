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
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_IDLE;
	_owner->SetState(State::Active);
	frameCount = 0;
}
