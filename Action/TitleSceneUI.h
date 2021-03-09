#pragma once

#include "GameObject.h"

class SpriteComponent;

/*
@file TitleUI.h
@brief �^�C�g����ʂ�UI��\��
*/

class TitleSceneUI :
    public GameObject
{
public:

    TitleSceneUI();
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~TitleSceneUI()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �^�C�g���摜�\���psprite
    SpriteComponent* sprite;

};

