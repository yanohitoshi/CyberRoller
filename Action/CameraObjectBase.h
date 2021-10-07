#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

/*
@file CameraObjectBase.h
@brief GameObject���p�������J�����̊��N���X
*/
class CameraObjectBase :
    public GameObject
{

public:

    /*
    @fn �R���X�g���N�^
    @param	�ė��p���邩�t���O
    @param	ObjectTag
    */
    CameraObjectBase(bool _reUseGameObject, const Tag _objectTag);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~CameraObjectBase();

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    virtual void UpdateGameObject(float _deltaTime = 1.0f);

    /*
    @fn ���͊֐�
    @brief	���͏������s��
    @param	_keyState ���͏��
    */
    virtual void GameObjectInput(const InputState& _keyState);

private:

};

