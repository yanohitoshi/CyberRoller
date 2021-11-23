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
	// 追跡開始条件を判定
	bool isStartTracking = _owner->GetIsTracking() && !_owner->GetIsDead() && frameCount > StayTime;

	// 条件を満たしていたら
	if (isStartTracking)
	{
		// 追跡状態に遷移
		state = EnemyState::ENEMY_STATE_TRACKING;
	}

	// 死亡状態か判定
	if (_owner->GetIsDead())
	{
		// 死亡状態に遷移
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
	// ステータスを有効化
	_owner->SetState(State::Active);
	frameCount = 0;
}
