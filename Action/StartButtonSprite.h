#pragma once
#include "GameObject.h"

// �N���X�̑O���錾
class SpriteComponent;

class StartButtonSprite :
    public GameObject
{
public:

    /*
    @brief	�R���X�g���N�^
    */
    StartButtonSprite();

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~StartButtonSprite();

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �X�v���C�gComponent
    SpriteComponent* sprite;

};

