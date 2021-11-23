//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ExplosionObjectBase.h"
#include "ExplosionObjectStateBase.h"

/*
@fn �R���X�g���N�^
@param	�I�u�W�F�N�g���ʗptag
*/
ExplosionObjectBase::ExplosionObjectBase(const Tag _objectTag)
	: GameObject(false, _objectTag)
	, hitPosition(Vector3::Zero)
	, firstPosition(Vector3::Zero)
	, fallArea(Vector3::Zero)
	, fallSpeed(0.0f)
{
}

/*
@brief �X�e�[�g�v�[���p�}�b�v�ɃX�e�[�g�N���X��ǉ�����֐�
@param	_state �ǉ�����X�e�[�g�N���X�̃|�C���^
@param	_stateTag ���ƂȂ�^�O
*/
void ExplosionObjectBase::AddStatePoolMap(ExplosionObjectStateBase* _state, ExplosionObjectState _stateTag)
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
void ExplosionObjectBase::RemoveStatePoolMap(ExplosionObjectState _stateTag)
{
	delete statePoolMap[_stateTag];
}

/*
@brief �X�e�[�g�v�[���p�}�b�v���N���A����
*/
void ExplosionObjectBase::ClearStatePoolMap()
{
	statePoolMap.clear();
}
