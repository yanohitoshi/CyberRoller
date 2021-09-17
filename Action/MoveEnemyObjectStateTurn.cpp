#include "MoveEnemyObjectStateTurn.h"

MoveEnemyObjectStateTurn::MoveEnemyObjectStateTurn()
{
}

MoveEnemyObjectStateTurn::~MoveEnemyObjectStateTurn()
{
}

EnemyState MoveEnemyObjectStateTurn::Update(EnemyObjectBase* _owner, float _deltaTime)
{

	// アニメーションの再生が終わっていたら
	if (!skeletalMeshComponent->IsPlaying())
	{
		_owner->SetMoveDirection(_owner->GetMoveDirection() * -1.0f);
		_owner->SetMoveDistance(_owner->GetMoveDistance() * -1.0f);
		// ステータスを待機状態にする
		state = EnemyState::ENEMY_STATE_MOVING;
	}

	if (_owner->GetIsDeadFlag())
	{
		state = EnemyState::ENEMY_STATE_DEAD;
	}

	return state;
}

void MoveEnemyObjectStateTurn::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_TURN));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_TURN;
	_owner->SetState(State::Active);
}

