#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

/*
@file SecondStageUI.h
@brief SecondStage��UI�\�����s��
*/
class SecondStageUI :
    public GameObject
{
public:
    /*
    @fn �R���X�g���N�^
    @brief  object�̐������s��
    */
    SecondStageUI(PlayerObject* _playerObject);
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~SecondStageUI();

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �V�[���̎��Ԑ����̒l
    const int SceneTime;
    class SkyBoxObject* skyBox;
};

