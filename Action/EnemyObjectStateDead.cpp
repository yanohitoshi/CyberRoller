//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectStateDead.h"

/*
@fn コンストラクタ
*/
EnemyObjectStateDead::EnemyObjectStateDead()
	: RespawnTime(120)
{
}

/*
@fn デストラクタ
*/
EnemyObjectStateDead::~EnemyObjectStateDead()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
EnemyState EnemyObjectStateDead::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	++frameCount;

	// 時間が来たらリスポーン
	if (frameCount >= RespawnTime)
	{
		skeletalMeshComponent->SetVisible(false);
		state = EnemyState::ENEMY_STATE_RESPAWN;
	}

	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
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
