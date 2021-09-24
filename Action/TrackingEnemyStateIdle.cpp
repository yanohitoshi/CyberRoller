#include "TrackingEnemyStateIdle.h"

TrackingEnemyStateIdle::TrackingEnemyStateIdle()
{
}

TrackingEnemyStateIdle::~TrackingEnemyStateIdle()
{
}

EnemyState TrackingEnemyStateIdle::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	state = EnemyState::ENEMY_STATE_MOVING;

	if (_owner->GetIsDeadFlag())
	{
		state = EnemyState::ENEMY_STATE_DEAD;
	}

	return state;
}

void TrackingEnemyStateIdle::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_IDLE;
	_owner->SetState(State::Active);
	RotationProcess(_owner, Vector3::NegUnitX, _owner->GetCharaForwardVec());
}
