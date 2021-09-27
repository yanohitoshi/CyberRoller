#include "MoveEnemyObjectStateDead.h"


MoveEnemyObjectStateDead::MoveEnemyObjectStateDead()
{
}

MoveEnemyObjectStateDead::~MoveEnemyObjectStateDead()
{
}

EnemyState MoveEnemyObjectStateDead::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	Vector3 nowScale = _owner->GetScaleVec();
	nowScale -= Vector3(0.01f, 0.01f, 0.01f);
	_owner->SetScale(nowScale);

	if (nowScale.x <= 0.0f)
	{
		skeletalMeshComponent->SetVisible(false);
		state = EnemyState::ENEMY_STATE_RESPAWN;
	}

	return state;
}

void MoveEnemyObjectStateDead::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_DEAD));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_DEAD;

	_owner->SetState(State::Disabling);
}