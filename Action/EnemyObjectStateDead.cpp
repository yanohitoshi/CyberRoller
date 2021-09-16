#include "EnemyObjectStateDead.h"

EnemyObjectStateDead::EnemyObjectStateDead()
{
}

EnemyObjectStateDead::~EnemyObjectStateDead()
{
}

EnemyState EnemyObjectStateDead::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// positionに速度を足してキャラクターを動かす
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	++frameCount;

	if (frameCount >= 300)
	{
		_owner->SetIsDeadFlag(false);
		state = EnemyState::ENEMY_STATE_IDLE;
	}

	return state;
}

void EnemyObjectStateDead::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_DEAD));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_DEAD;
	_owner->SetState(State::Disabling);
	frameCount = 0;
}