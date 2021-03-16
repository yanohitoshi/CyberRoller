#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class SpriteComponent;
class CountDownFont;

/*
@file WarningSprite.h
@brief ���Ԍo�߂�m�点��UI��\��
*/
class WarningSprite :
    public GameObject
{
public:
    
    /*
    @fn �R���X�g���N�^
    @brief	�R���X�g���N�^ 
    @param	�e�ƂȂ�CountDownFont�^�|�C���^
    */
    WarningSprite(CountDownFont* _owner);
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~WarningSprite();

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    // owner���i�[���邽�߂̃|�C���^�ϐ�
    CountDownFont* owner;
    // SpriteComponent�̃|�C���^�ϐ�
    SpriteComponent* sprite;
    // fadein�Eout��؂�ւ���t���O
    bool fadeFlag;
    // alpha�l
    float alpha;
    // ����fadein�Eout�������𐔂���J�E���g
    int count;
};

