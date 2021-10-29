//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CameraObjectBase.h"

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

void CameraObjectBase::RemoveStatePoolMap(CameraState _stateTag)
{
	delete statePoolMap[_stateTag];
}

void CameraObjectBase::ClearStatePoolMap()
{
	statePoolMap.clear();
}
