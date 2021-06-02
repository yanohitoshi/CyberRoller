#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

/*
@file FinalStageUI.h
@brief FinalStage��ʂł�UI�̕\�����s��
*/
class FinalStageUI :
    public GameObject
{
public:
    /*
    @fn �R���X�g���N�^
    @brief  object�̐������s��
    */
    FinalStageUI(PlayerObject* _playerObject);
    
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
    
private:

    // �V�[���̎��Ԑ����̒l
    const int SceneTime;
};

