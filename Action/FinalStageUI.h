#pragma once
#include "GameObject.h"

/*
@file FinalStageUI.h
@brief FinalStage��ʂł�UI�̕\�����s��
*/

class FinalStageUI :
    public GameObject
{
public:
    
    FinalStageUI();
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~FinalStageUI();
    
    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;
    
    // �^�C���I�[�o�[����p�t���O
    static bool timeOverFlag;
    
    // �J�E���g�X�^�[�g����p�t���O
    static bool countStartFlag;

private:

};

