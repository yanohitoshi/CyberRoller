//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "MoveEnemyObjectStateTurn.h"

/*
@fn コンストラクタ
*/
MoveEnemyObjectStateTurn::MoveEnemyObjectStateTurn()
{
}

/*
@fn デストラクタ
*/
MoveEnemyObjectStateTurn::~MoveEnemyObjectStateTurn()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
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

	// 死亡状態か判定
	if (_owner->GetIsDead())
	{
		// 死亡状態に遷移
		state = EnemyState::ENEMY_STATE_DEAD;
	}

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
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