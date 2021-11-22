//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CameraObjectBase.h"
#include "CameraObjectStateBase.h"

/*
@fn �R���X�g���N�^
@param	�ė��p���邩�t���O
@param	ObjectTag
*/
CameraObjectBase::CameraObjectBase(bool _reUseGameObject, const Tag _objectTag)
	: GameObject(_reUseGameObject, _objectTag)
	, DeltaCorrection(8.0f)
	, offSetPosition(Vector3(Vector3::Zero))
{
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
CameraObjectBase::~CameraObjectBase()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void CameraObjectBase::UpdateGameObject(float _deltaTime)
{
}

/*
@fn ���͊֐�
@brief	���͏������s��
@param	_keyState ���͏��
*/
void CameraObjectBase::GameObjectInput(const InputState& _keyState)
{
}

/*
@brief �X�e�[�g�v�[���p�}�b�v�ɃX�e�[�g�N���X��ǉ�����֐�
@param	_state �ǉ�����X�e�[�g�N���X�̃|�C���^
@param	_stateTag ���ƂȂ�^�O
*/
void CameraObjectBase::AddStatePoolMap(CameraObjectStateBase* _state, CameraState _stateTag)
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
void CameraObjectBase::RemoveStatePoolMap(CameraState _stateTag)
{
	delete statePoolMap[_stateTag];
}

/*
@brief �X�e�[�g�v�[���p�}�b�v���N���A����
*/
void CameraObjectBase::ClearStatePoolMap()
{
	statePoolMap.clear();
}
