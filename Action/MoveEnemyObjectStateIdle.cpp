//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "MoveEnemyObjectStateIdle.h"

/*
@fn コンストラクタ
*/
MoveEnemyObjectStateIdle::MoveEnemyObjectStateIdle()
{
}

/*
@fn デストラクタ
*/
MoveEnemyObjectStateIdle::~MoveEnemyObjectStateIdle()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
@return EnemyState 次のステータス
*/
EnemyState MoveEnemyObjectStateIdle::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// positionに速度を足してキャラクターを動かす
	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	state = EnemyState::ENEMY_STATE_MOVING;

	if (_owner->GetIsDead())
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
void MoveEnemyObjectStateIdle::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_IDLE));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_IDLE;
	_owner->SetState(State::Active);
}