#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class SpriteComponent;

/*
@file TitleBackGroundSprite.h
@brief �^�C�g���̔w�i��\������
*/
class TitleBackGroundSprite :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    */
    TitleBackGroundSprite();
   
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~TitleBackGroundSprite();
    
    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �w�i�p�X�v���C�gComponent
    SpriteComponent* sprite;

};

