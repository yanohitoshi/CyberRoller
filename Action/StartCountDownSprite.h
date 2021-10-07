#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class SpriteComponent;
class Texture;

enum TimeNum
{
    ZERO = 0,
    ONE = 1,
    TOW = 2,
    TREE = 3,
};

/*
@file StartCountDownSprite.h
@brief �Q�[���J�n�p�J�E���g�_�E����\������
*/
class StartCountDownSprite :
    public GameObject
{
public:
    
    /*
    @brief	�R���X�g���N�^
    */
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

    /*
    @fn �J�E���g�_�E���\�����ԃJ�E���g�𐔂���֐�
    */
    void ChackCountProcess();

    /*
    @fn �e�N�X�`���̏�Ԃ�����֐�
    */
    void ChackTextureProcess();

    /*
    @fn �e�N�X�`����؂�ւ���֐�
    */
    void ChangeTextureProcess();

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

