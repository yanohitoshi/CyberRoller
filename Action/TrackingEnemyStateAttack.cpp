#include "TrackingEnemyStateAttack.h"

TrackingEnemyStateAttack::TrackingEnemyStateAttack()
{
}

TrackingEnemyStateAttack::~TrackingEnemyStateAttack()
{
}

EnemyState TrackingEnemyStateAttack::Update(EnemyObjectBase* _owner, float _deltaTime)
{

	// アニメーションの再生が終わっていたら
	if (!skeletalMeshComponent->IsPlaying())
	{
		_owner->SetIsAttack(false);
		state = EnemyState::ENEMY_STATE_IDLE;
	}

	return state;
}

void TrackingEnemyStateAttack::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_ATTACK));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_ATTACK;

	_owner->SetState(State::Active);
}