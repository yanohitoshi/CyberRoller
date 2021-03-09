#pragma once
#include "GameObject.h"

class SpriteComponent;

/*
@file ThankYouSprite.h
@brief ���U���g��ʂ�\������
*/

class ThankYouSprite :
    public GameObject
{
public:

    ThankYouSprite();
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~ThankYouSprite();

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �X�v���C�gComponent
    SpriteComponent* sprite;
    // �t���[���J�E���g
    int frameCount;
    // �`�悷�邩�ǂ����t���O
    bool visibleFlag;

};

