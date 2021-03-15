#pragma once
#include "GameObject.h"
#include "SDL_TTF.h"

/*
@file FirstStageUI.h
@brief FirstStage��UI�\�����s��
*/

class FirstStageUI :
    public GameObject
{
public:
    /*
    @fn �R���X�g���N�^
    @brief  object�̐������s��
    */
    FirstStageUI();
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~FirstStageUI();
    
    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;
    
private:

};


