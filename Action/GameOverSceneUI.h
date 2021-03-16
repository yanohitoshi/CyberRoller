#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class SpriteComponent;

/*
@file GameOverSceneUI.h
@brief GameOverScene��ʂł�UI�̕\�����s��
*/
class GameOverSceneUI :
    public GameObject
{
public:
    /*
    @fn �R���X�g���N�^
    @brief  object�̐������s��
    */
    GameOverSceneUI();
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~GameOverSceneUI();
    
    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // GameOver�摜�\���psprite
    SpriteComponent* sprite;

};

