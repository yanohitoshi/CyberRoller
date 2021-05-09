#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class SpriteComponent;
class Texture;

/*
@file StartCountDownSprite.h
@brief �Q�[���J�n�p�J�E���g�_�E����\������
*/
class StartCountDownSprite :
    public GameObject
{
public:

    StartCountDownSprite();

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~StartCountDownSprite()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �X�v���C�gComponent
    SpriteComponent* sprite;
    // texture 1�p
    Texture* firstTexure;
    // texture 2�p
    Texture* secondTexure;
    // texture 3�p
    Texture* thirdTexure;
    // texture Start�p
    Texture* startTexure;

    // texture�ύX�t���O
    bool texChangeFlag;
    // �`��t���O
    bool drawSpriteFlag;

    // texture��؂�ւ���^�C�~���O����p�̒萔�J�E���g
    const int ChangeCount;

    // �t���[���J�E���g
    int frameCount;
    // �\������
    int time;
    // �J�E���g�_�E���J�n����^�C�~���O�����邽�߂̃J�E���g
    int timeStartCount;
};

