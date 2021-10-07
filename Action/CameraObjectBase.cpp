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