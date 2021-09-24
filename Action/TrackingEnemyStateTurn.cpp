#include "TrackingEnemyStateTurn.h"

TrackingEnemyStateTurn::TrackingEnemyStateTurn()
{
}

TrackingEnemyStateTurn::~TrackingEnemyStateTurn()
{
}

EnemyState TrackingEnemyStateTurn::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// アニメーションの再生が終わっていたら
	if (!skeletalMeshComponent->IsPlaying())
	{
		// ステータスを待機状態にする
		state = EnemyState::ENEMY_STATE_REPOSITION;
	}

	if (_owner->GetIsDeadFlag())
	{
		state = EnemyState::ENEMY_STATE_DEAD;
	}

	return state;
}

void TrackingEnemyStateTurn::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_TURN));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_TURN;
	_owner->SetState(State::Active);
}
