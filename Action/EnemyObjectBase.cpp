//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectBase.h"
#include "EnemyDeadEffectManager.h"

/*
@fn �R���X�g���N�^
@brief �ʏ�̃G�l�~�[�̃R���X�g���N�^
@param	�|�W�V����
@param	�ė��p���邩�t���O
@param	�I�u�W�F�N�g���ʗptag
@param	�ǐՑΏ�
*/
EnemyObjectBase::EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag, GameObject* _trackingObject)
	: GameObject(_reUseGameObject, _objectTag)
	, enemyBox({ Vector3::Zero,Vector3::Zero })
	, trackingObject(_trackingObject)
	, respawnPositionOffset(1000.0f)
	, Size(Vector3(2.0f,2.0f,2.0f))
{
	// �����o�[�ϐ�������
	SetPosition(_pos);
	tag = _objectTag;
	firstPosition = _pos;
	respawnPosition = firstPosition;
	respawnPosition.z += respawnPositionOffset;
	isVisible = true;
	// ���S���̃G�t�F�N�g��t�^
	new EnemyDeadEffectManager(this);
}

/*
@fn �R���X�g���N�^
@brief �ړ�����G�l�~�[�̃R���X�g���N�^
@param	�|�W�V����
@param	�ė��p���邩�t���O
@param	�I�u�W�F�N�g���ʗptag
@param	�ړ����x
@param	�ړ�����
@param	�ړ�����
*/
EnemyObjectBase::EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag, GameObject* _trackingObject, MoveEnemyData _moveEnemyData)
	: GameObject(_reUseGameObject, _objectTag)
	, enemyBox({ Vector3::Zero,Vector3::Zero })
	, trackingObject(_trackingObject)
	, moveDirection(_moveEnemyData.direction)
	, moveDistance(_moveEnemyData.distance)
	, moveSpeed(_moveEnemyData.speed)
	, moveEnemyTag(_moveEnemyData.tag)
	, respawnPositionOffset(1000.0f)
	, Size(Vector3(2.0f, 2.0f, 2.0f))
{
	// �����o�[�ϐ�������
	tag = _objectTag;
	SetPosition(_pos);
	firstPosition = _pos;
	respawnPosition = firstPosition;
	respawnPosition.z += respawnPositionOffset;

	isVisible = true;

	// ���S���̃G�t�F�N�g��t�^
	new EnemyDeadEffectManager(this);
}

/*
@fn �R���X�g���N�^
@brief �ړ�����G�l�~�[�̃R���X�g���N�^
@param	�|�W�V����
@param	�ė��p���邩�t���O
@param	�I�u�W�F�N�g���ʗptag
@param	�ړ����x
@param	�ǐՑΏ�
*/
EnemyObjectBase::EnemyObjectBase(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag, float _moveSpeed, GameObject* _trackingObject)
	: GameObject(_reUseGameObject, _objectTag)
	, enemyBox({ Vector3::Zero,Vector3::Zero })
	, moveSpeed(_moveSpeed)
	, trackingObject(_trackingObject)
	, respawnPositionOffset(1000.0f)
	, BoxMin(Vector3(-10.0f, -10.0f, 0.0f))
	, BoxMax(Vector3(10.0f, 10.0f, 10.0f))
	, Size(Vector3(2.0f, 2.0f, 2.0f))
{
	// �����o�[�ϐ�������
	tag = _objectTag;
	SetPosition(_pos);
	firstPosition = _pos;
	respawnPosition = firstPosition;
	respawnPosition.z += respawnPositionOffset;

	isVisible = true;

	// ���S���̃G�t�F�N�g��t�^
	new EnemyDeadEffectManager(this);
}

/*
@fn Animation��getter�֐�
@param _state ���݂̃G�l�~�[�̃X�e�[�^�X
@return Animation Animation�N���X�̃|�C���^��Ԃ�
*/
const Animation* EnemyObjectBase::GetAnimation(EnemyState _state)
{
	// _state�Ԗڂ̃A�j���[�V������Ԃ�
	return animTypes[static_cast<unsigned int>(_state)];
}
