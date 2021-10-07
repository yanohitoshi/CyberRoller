#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class SpriteComponent;

/*
@file ContinueSprite.h
@brief �R���e�j���[�p�摜��\������
*/
class ContinueSprite :
    public GameObject
{
public:

    /*
    @brief	�R���X�g���N�^
    */
    ContinueSprite();
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~ContinueSprite();
    
    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

    /*
    @brief	����
    @param	���͏��
    */
    void GameObjectInput(const InputState& _keyState)override;



private:

    /*
    @brief	���͏������ɕ`���؂�ւ���
    @param	���͏��
    */
    void ChackKeyProcess(const InputState& _keyState);

    // �X�v���C�gComponent
    SpriteComponent* sprite;

    // �`�悷�邩�ǂ����t���O
    bool visibleFlag;
    // �`�悳��Ă��邩�t���O
    static bool drawFlag;
    // �R���e�j���[�������ǂ����t���O
    static bool continueFlag;

    // �`���؂�ւ���J�E���g��r�p�̒萔
    const int DrawCount;
    // �t���[���J�E���g
    int frameCount;

public://�Q�b�^�[�Z�b�^�[

    /*
    @fn drawFlag��getter�֐�
    @brief	drawFlag���擾
    @return	�`�悳��Ă��邩�t���O
    */
    static bool GetDrawFlag() { return drawFlag; }
    
    /*
    @fn continueFlag��getter�֐�
    @brief	continueFlag���擾
    @return	�R���e�j���[�������ǂ����t���O
    */
    static bool GetContinueFlag() { return continueFlag; }

};

