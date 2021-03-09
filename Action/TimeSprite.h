#pragma once

#include "GameObject.h"

class SpriteComponent;
class Texture;

/*
@file TimeSprite.h
@brief ���ԕ\���t���[���p��UI��\��
*/

class TimeSprite :
    public GameObject
{
public:

    TimeSprite();
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~TimeSprite();

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �X�v���C�gComponent
    SpriteComponent* sprite;
    // texture
    Texture* tex;
    // �t���[���J�E���g�ϐ�
    int frameCount;
};

