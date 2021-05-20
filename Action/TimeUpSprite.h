#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class SpriteComponent;

/*
@file TimeUpSprite.h
@brief �^�C���I�[�o�[�pUI��\��
*/
class TimeUpSprite :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    */
    TimeUpSprite();
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~TimeUpSprite();

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

    /*
    @brief	�`�悳��Ă��邩�t���O��getter
    @return	bool �`�悳��Ă��邩�t���O
    */

    static bool GetDrawFlag() { return drawFlag; }
private:

    // �X�v���C�gComponent
    SpriteComponent* sprite;
    // �t���[���J�E���g
    int frameCount;

    // �`���؂�ւ���J�E���g��r�p�̒萔
    const int DrawCount;

    // 1�x�����`�悷�邽�߂̃t���O
    bool visibleFlag;

    // �`�悳��Ă��邩�t���O
    static bool drawFlag;
};

