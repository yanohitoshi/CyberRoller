//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectBase.h"
#include "EnemyDeadEffectManager.h"
#include "EnemyObjectStateBase.h"

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
	, BoxMin(Vector3(-30.0f, -30.0f, -10.0f))
	, BoxMax(Vector3(10.0f, 10.0f, 60.0f))
{
	// �����o�[�ϐ�������
	SetPosition(_pos);
	tag = _objectTag;
	firstPosition = _pos;
	respawnPosition = firstPosition;
	respawnPosition.z += respawnPositionOffset;
	isVisible = true;
	defeatedObjectPosition = Vector3::Zero;
	attackObjectPosition = Vector3::Zero;
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
	, BoxMin(Vector3(-30.0f, -30.0f, -10.0f))
	, BoxMax(Vector3(10.0f, 10.0f, 60.0f))
{
	// �����o�[�ϐ�������
	tag = _objectTag;
	SetPosition(_pos);
	firstPosition = _pos;
	respawnPosition = firstPosition;
	respawnPosition.z += respawnPositionOffset;
	defeatedObjectPosition = Vector3::Zero;
	attackObjectPosition = Vector3::Zero;
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
	, BoxMin(Vector3(-30.0f, -30.0f, -10.0f))
	, BoxMax(Vector3(10.0f, 10.0f, 60.0f))
	, Size(Vector3(2.0f, 2.0f, 2.0f))
{
	// �����o�[�ϐ�������
	tag = _objectTag;
	SetPosition(_pos);
	firstPosition = _pos;
	respawnPosition = firstPosition;
	respawnPosition.z += respawnPositionOffset;
	defeatedObjectPosition = Vector3::Zero;
	attackObjectPosition = Vector3::Zero;
	isVisible = true;

	// ���S���̃G�t�F�N�g��t�^
	new EnemyDeadEffectManager(this);
}

/*
@brief �X�e�[�g�v�[���p�}�b�v�ɃX�e�[�g�N���X��ǉ�����֐�
@param	_state �ǉ�����X�e�[�g�N���X�̃|�C���^
@param	_stateTag ���ƂȂ�^�O
*/
void EnemyObjectBase::AddStatePoolMap(EnemyObjectStateBase* _state, EnemyState _stateTag)
{
	//�}�b�v�̒��ɒǉ�����A�N�^�[�̃R���e�i�����邩�ǂ����𒲂ׂ�
	auto stateMaps = statePoolMap.find(_stateTag);

	//����Ƃ�
	if (stateMaps != statePoolMap.end())
	{
		return;
	}
	else //�Ȃ��Ƃ�
	{
		statePoolMap[_stateTag] = _state;
	}
}

/*
@brief �X�e�[�g�v�[���p�}�b�v����X�e�[�g�N���X���폜����֐�
@param	_stateTag ���ƂȂ�^�O
*/
void EnemyObjectBase::RemoveStatePoolMap(EnemyState _stateTag)
{
	delete statePoolMap[_stateTag];
}

/*
@brief �X�e�[�g�v�[���p�}�b�v���N���A����
*/
void EnemyObjectBase::ClearStatePoolMap()
{
	statePoolMap.clear();
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
