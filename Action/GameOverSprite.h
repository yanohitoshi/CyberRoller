#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class SpriteComponent;

/*
@file GameOverSprite.h
@brief �Q�[���I�[�o�[�̎��p��UI��\������
*/
class GameOverSprite :
    public GameObject
{
public:

    GameOverSprite();
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~GameOverSprite();

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
    // �`�悷�邩�t���O
    bool visibleFlag;

};

