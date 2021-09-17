#include "NormalEnemyObjectStateIdle.h"

NormalEnemyObjectStateIdle::NormalEnemyObjectStateIdle()
{
}

NormalEnemyObjectStateIdle::~NormalEnemyObjectStateIdle()
{
}

EnemyState NormalEnemyObjectStateIdle::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// positionに速度を足してキャラクターを動かす
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	if (_owner->GetIsDeadFlag())
	{
		state = EnemyState::ENEMY_STATE_DEAD;
	}

	return state;
}

void NormalEnemyObjectStateIdle::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_IDLE;
	_owner->SetState(State::Active);
}
