#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class SpriteComponent;

/*
@file GameClearSprite.h
@brief �Q�[���N���A�p�摜��\������
*/
class GameClearSprite :
    public GameObject
{
public:

    GameClearSprite();
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~GameClearSprite();
    
    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    SpriteComponent* sprite;
    int frameCount;
    bool visibleFlag;

    // �`���؂�ւ���J�E���g��r�p�̒萔
    const int DRAW_COUNT;

};

