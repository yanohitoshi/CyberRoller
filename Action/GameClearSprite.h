#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class SpriteComponent;
class PlayerObject;

/*
@file GameClearSprite.h
@brief �Q�[���N���A�p�摜��\������
*/
class GameClearSprite :
    public GameObject
{
public:
    
    /*
    @brief	�R���X�g���N�^
    @param	_playerObject �v���C���[�I�u�W�F�N�g�̃|�C���^
    */
    GameClearSprite(PlayerObject* _playerObject);
    
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

    // spriteComponent�̃|�C���^�ϐ�
    SpriteComponent* sprite;

    // playerobject�̃|�C���^���i�[���邽�߂̃|�C���^�ϐ�
    PlayerObject* playerObject;
    
    // �`�悷�邩�ǂ����t���O
    bool visibleFlag;

    // �t���[�����J�E���g����ϐ�
    int frameCount;
    // �`���؂�ւ���J�E���g��r�p�̒萔
    const int DrawCount;
};
