#pragma once

#include "GameObject.h"

class SpriteComponent;

/*
@file ResultUI.h
@brief ���U���g��ʂł�UI�̕\�����s��
*/

class ClearSceneUI :
    public GameObject
{
public:
    /*
    @fn �R���X�g���N�^
    @brief  object�̐������s��
    */
    ClearSceneUI();
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~ClearSceneUI();   

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �N���A�摜�\���psprite
    SpriteComponent* sprite;

};

