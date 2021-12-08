#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "SDL_TTF.h"

// �N���X�̑O���錾
class PlayerObject;

/*
@file FirstStageUI.h
@brief FirstStage��UI�\�����s��
*/
class TutorialStageUI :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @brief  object�̐������s��
    */
    TutorialStageUI();
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~TutorialStageUI();
    
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
    // �X�J�C�{�b�N�X�N���X�̃|�C���^�ϐ�
    class SkyBoxObject* skyBox;
};
