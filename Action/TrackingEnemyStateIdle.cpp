//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TrackingEnemyStateIdle.h"

/*
@fn コンストラクタ
*/
TrackingEnemyStateIdle::TrackingEnemyStateIdle()
	: StayTime(60)
{
}

/*
@fn デストラクタ
*/
TrackingEnemyStateIdle::~TrackingEnemyStateIdle()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
EnemyState TrackingEnemyStateIdle::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	++frameCount;
	if (_owner->GetIsTracking() && !_owner->GetIsDeadFlag() && frameCount > StayTime)
	{
		state = EnemyState::ENEMY_STATE_TRACKING;
	}

	if (_owner->GetIsDeadFlag())
	{
		state = EnemyState::ENEMY_STATE_DEAD;
	}

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void TrackingEnemyStateIdle::Enter(EnemyObjectBase* _owner, float _deltaTime)
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
