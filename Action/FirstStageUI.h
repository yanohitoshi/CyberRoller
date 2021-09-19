#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "SDL_TTF.h"

class PlayerObject;

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

    // �W�����v�`���[�g���A����\��������W�萔
    const Vector3 JumpTutorialPosition;
    // �ړ��`���[�g���A����\��������W�萔
    const Vector3 MoveTutorialPosition;
    // �W�����v�U���`���[�g���A����\��������W�萔
    const Vector3 JumpAttackTutorialPosition;

    class SkyBoxObject* skyBox;
};


