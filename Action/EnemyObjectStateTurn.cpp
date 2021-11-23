//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectStateTurn.h"

/*
@fn コンストラクタ
*/
EnemyObjectStateTurn::EnemyObjectStateTurn()
{
}

/*
@fn デストラクタ
*/
EnemyObjectStateTurn::~EnemyObjectStateTurn()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
EnemyState EnemyObjectStateTurn::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	// アニメーションの再生が終わっていたら
	if (!skeletalMeshComponent->IsPlaying())
	{
		// ステータスを待機状態にする
		state = EnemyState::ENEMY_STATE_REPOSITION;
	}

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
void EnemyObjectStateTurn::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
	// ownerからownerのskeletalMeshComponentのポインタをもらう
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	// 再生するアニメーションをもらい再生をかける
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(EnemyState::ENEMY_STATE_TURN));
	// stateを待機状態にして保存
	state = EnemyState::ENEMY_STATE_TURN;
	// ステータスをActiveにset
	_owner->SetState(State::Active);
}
