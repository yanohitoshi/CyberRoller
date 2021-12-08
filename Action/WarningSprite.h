#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class SpriteComponent;
class CountDownFont;
class SoundEffectComponent;

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

    /*
    @fn �t�F�[�h�C���A�E�g�̏�Ԃ�����֐�
    */
    void CheckFadeInOutProcess();
    
    /*
    @fn �t�F�[�h�C���A�E�g�����֐�
    */
    void FadeInOutProcess();
    
    /*
    @fn �Ō�̃t�F�[�h�A�E�g�����֐�
    */
    void LastFadeOutProcess();
    
    /*
    @fn �t�F�[�h�C���A�E�g�̐؂�ւ������֐�
    */
    void ChangeFadeProcess();

    // owner���i�[���邽�߂̃|�C���^�ϐ�
    CountDownFont* owner;
    // SpriteComponent�̃|�C���^�ϐ�
    SpriteComponent* sprite;
    // �T�E���h�G�t�F�N�g�N���X
    SoundEffectComponent* soundEffect;

    // �T�E���h�G�t�F�N�g���Đ����邩�ǂ���
    bool isPlaySound;
    // fadein�Eout��؂�ւ���t���O
    bool fadeFlag;
    // alpha�l
    float alpha;
    // ����fadein�������𐔂���J�E���g
    int fadeinCount;

    // �t�F�[�h�C���A�E�g�ɗp����l�萔
    const float FadeValue;
    // �t�F�[�h�C���ɐ؂�ւ���K��l�萔
    const float ChangeFadeInValue;
    // �t�F�[�h�A�E�g�ɐ؂�ւ���K��l�萔
    const float ChangeFadeOutValue;
};
