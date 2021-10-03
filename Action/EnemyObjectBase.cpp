#include "EnemyObjectBase.h"
#include "EnemyDeadEffectManager.h"
EnemyObjectBase::EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
	, enemyBox({ Vector3::Zero,Vector3::Zero })
	, respawnPositionOffset(1600.0f)
{
	SetPosition(_pos);
	tag = _objectTag;
	firstPosition = _pos;
	respawnPosition = firstPosition;
	respawnPosition.z += respawnPositionOffset;
	new EnemyDeadEffectManager(this);
}

EnemyObjectBase::EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag, float _moveSpeed,const Vector3& _moveDir, float _moveDistance, MoveEnemyTag _moveEnemyTag)
	: GameObject(_reUseGameObject, _objectTag)
	, enemyBox({ Vector3::Zero,Vector3::Zero })
	,moveDirection(_moveDir)
	,moveDistance(_moveDistance)
	,moveSpeed(_moveSpeed)
	,moveEnemyTag(_moveEnemyTag)
	, respawnPositionOffset(1600.0f)
{
	tag = _objectTag;
	SetPosition(_pos);
	firstPosition = _pos;
	respawnPosition = firstPosition;
	respawnPosition.z += respawnPositionOffset;
	new EnemyDeadEffectManager(this);
}

EnemyObjectBase::EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag, float _moveSpeed, GameObject* _trackingObject)
	: GameObject(_reUseGameObject, _objectTag)
	, enemyBox({ Vector3::Zero,Vector3::Zero })
	, moveSpeed(_moveSpeed)
	, trackingObject(_trackingObject)
	, respawnPositionOffset(1600.0f)
{
	tag = _objectTag;
	SetPosition(_pos);
	firstPosition = _pos;
	respawnPosition = firstPosition;
	respawnPosition.z += respawnPositionOffset;
	new EnemyDeadEffectManager(this);
}

void EnemyObjectBase::EnemyCalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec)
{
	// ���x�x�N�g��������
	_calcFixVec = Vector3::Zero;

	// Box�𗘗p���Ĕ�������p�̕ϐ��v�Z
	float dx1 = _fixedBox.min.x - _movableBox.max.x;
	float dx2 = _fixedBox.max.x - _movableBox.min.x;
	float dy1 = _fixedBox.min.y - _movableBox.max.y;
	float dy2 = _fixedBox.max.y - _movableBox.min.y;
	float dz1 = _fixedBox.min.z - _movableBox.max.z;
	float dz2 = _fixedBox.max.z - _movableBox.min.z;

	// dx, dy, dz �ɂ� ���ꂼ��1,2�̂�����Βl�������������Z�b�g����
	float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
	float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;
	float dz = (Math::Abs(dz1) < Math::Abs(dz2)) ? dz1 : dz2;

	// x, y, z�̂����ł��������������ňʒu�𒲐�
	if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
	{
		// x��������x�������ɉ����߂�
		_calcFixVec.x = dx;
	}
	else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
	{
		// y��������x�������ɉ����߂�
		_calcFixVec.y = dy;
	}
	else
	{
		// z��������x�������ɉ����߂�
		_calcFixVec.z = dz;
	}
}

const Animation* EnemyObjectBase::GetAnimation(EnemyState _state)
{
	// _state�Ԗڂ̃A�j���[�V������Ԃ�
	return animTypes[static_cast<unsigned int>(_state)];
}
