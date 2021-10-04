#include "TrackingEnemyStateMoving.h"

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
