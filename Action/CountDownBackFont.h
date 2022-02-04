#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class SpriteComponent;
class Texture;
class Font;
class CountDownFont;

/*
@file CountDownBackFont.h
@brief �J�E���g�_�E���̉e�̕\�����s��
*/
class CountDownBackFont :
    public GameObject
{
public:

    /*
    @brief	�R���X�g���N�^
    @param	�J�E���g���鎞��
    */
    CountDownBackFont(CountDownFont* _owner,int _time);
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~CountDownBackFont();

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // SpriteComponent�ϐ�
    SpriteComponent* sprite;
    CountDownFont* owner;
    // �t���[���J�E���g
    int frameCount;
    // �v�����鎞��
    int time;

    // ���Ԃ�1�i�߂�^�C�~���O���r����萔
    const int AddTimeCount;
};

