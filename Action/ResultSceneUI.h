#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

/*
@file ResultSceneUI.h
@brief ResultScene��ʂł�UI�̕\�����s��
*/
class ResultSceneUI :
    public GameObject
{
public:
    /*
    @fn �R���X�g���N�^
    @brief  object�̐������s��
    */
    ResultSceneUI();
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~ResultSceneUI();

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    class SkyBoxObject* skyBox;
};

