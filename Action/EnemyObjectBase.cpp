#include "EnemyObjectBase.h"
#include "EnemyDeadEffectManager.h"

EnemyObjectBase::EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
	, enemyBox({ Vector3::Zero,Vector3::Zero })
	, respawnPositionOffset(1600.0f)
{
	// �����o�[�ϐ�������
	SetPosition(_pos);
	tag = _objectTag;
	firstPosition = _pos;
	respawnPosition = firstPosition;
	respawnPosition.z += respawnPositionOffset;

	// ���S���̃G�t�F�N�g��t�^
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
	// �����o�[�ϐ�������
	tag = _objectTag;
	SetPosition(_pos);
	firstPosition = _pos;
	respawnPosition = firstPosition;
	respawnPosition.z += respawnPositionOffset;

	// ���S���̃G�t�F�N�g��t�^
	new EnemyDeadEffectManager(this);
}

EnemyObjectBase::EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag, float _moveSpeed, GameObject* _trackingObject)
	: GameObject(_reUseGameObject, _objectTag)
	, enemyBox({ Vector3::Zero,Vector3::Zero })
	, moveSpeed(_moveSpeed)
	, trackingObject(_trackingObject)
	, respawnPositionOffset(1600.0f)
	, BoxMin(Vector3(-10.0f, -10.0f, 0.0f))
	, BoxMax(Vector3(10.0f, 10.0f, 10.0f))
{
	// �����o�[�ϐ�������
	tag = _objectTag;
	SetPosition(_pos);
	firstPosition = _pos;
	respawnPosition = firstPosition;
	respawnPosition.z += respawnPositionOffset;

	// ���S���̃G�t�F�N�g��t�^
	new EnemyDeadEffectManager(this);
}

const Animation* EnemyObjectBase::GetAnimation(EnemyState _state)
{
	// _state�Ԗڂ̃A�j���[�V������Ԃ�
	return animTypes[static_cast<unsigned int>(_state)];
}
