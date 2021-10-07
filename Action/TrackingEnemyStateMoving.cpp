//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TrackingEnemyStateMoving.h"

// 現在のstatePatternの仕様空のクラスを追加しないといけない場合がありそのための空のクラスです。
// 改善方法模索中です。

/*
@fn コンストラクタ
*/
TrackingEnemyStateMoving::TrackingEnemyStateMoving()
{
}

/*
@fn デストラクタ
*/
TrackingEnemyStateMoving::~TrackingEnemyStateMoving()
{
}

/*
@fn アップデート
@brief	stateに応じてアップデートを行う
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
EnemyState TrackingEnemyStateMoving::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	return state;
}

/*
@fn state変更時の初期化
@param	_owner 親クラスのポインタ
@param	_deltaTime 最後のフレームを完了するのに要した時間
*/
void TrackingEnemyStateMoving::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
}
