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
    ThirdStageUI(PlayerObject* _playerObject);
    
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


private:

    // �V�[���̎��Ԑ����̒l
    const int SceneTime;
    // �X�J�C�{�b�N�X�N���X�̃|�C���^�ϐ�
    class SkyBoxObject* skyBox;
};

