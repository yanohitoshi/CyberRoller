#include "TrackingEnemyStateMoving.h"

// ���݂�statePattern�̎d�l��̃N���X��ǉ����Ȃ��Ƃ����Ȃ��ꍇ�����肻�̂��߂̋�̃N���X�ł��B
// ���P���@�͍����ł��B

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
