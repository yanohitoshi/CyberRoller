#include "TrackingEnemyStateMoving.h"

// 現在のstatePatternの仕様空のクラスを追加しないといけない場合がありそのための空のクラスです。
// 改善方法模索中です。

TrackingEnemyStateMoving::TrackingEnemyStateMoving()
{
}

TrackingEnemyStateMoving::~TrackingEnemyStateMoving()
{
}

EnemyState TrackingEnemyStateMoving::Update(EnemyObjectBase* _owner, float _deltaTime)
{
	return state;
}

void TrackingEnemyStateMoving::Enter(EnemyObjectBase* _owner, float _deltaTime)
{
}
