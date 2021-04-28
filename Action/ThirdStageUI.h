#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

/*
@file ThirdStageUI.h
@brief ThirdStage��UI�\�����s��
*/
class ThirdStageUI :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @brief  object�̐������s��
    */
    ThirdStageUI();
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~ThirdStageUI();

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

    // �V�[���̎��Ԑ����̒l
    const int SCENE_TIME;

};

