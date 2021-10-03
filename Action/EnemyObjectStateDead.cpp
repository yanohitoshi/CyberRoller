#include "EnemyObjectStateDead.h"

EnemyObjectStateDead::EnemyObjectStateDead()
{
}

EnemyObjectStateDead::~EnemyObjectStateDead()
{
}

EnemyState EnemyObjectStateDead::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	++frameCount;

	if (frameCount >= 120)
	{
		skeletalMeshComponent->SetVisible(false);
		state = EnemyState::ENEMY_STATE_RESPAWN;
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
