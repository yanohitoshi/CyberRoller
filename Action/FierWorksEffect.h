#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"
#include "CrystalEffectManager.h"

/*
@file FierWorksEffect.h
@brief FierWorksEffect�̐����ƍX�V���s��
*/
class FierWorksEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�|�W�V����
    @param	�ړ����x
    @param	���F������pTag
    */
    FierWorksEffect(const Vector3& _pos, const Vector3& _velocity , CrystalColor _crystalColor);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~FierWorksEffect()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    
    /*
    @fn �t�F�[�h�C���֐�
    */
    void FadeInProcess();

    /*
    @fn ���x�}���֐�
    */
    void ChackSpeedProcess();

    // �t�F�[�h�C���t���O
    bool inFlag;

    // ���x�Ɍ�����������ۂ̒萔
    const float SubSpeed;
    // �t�F�[�h�C�����̖��t���[������scale�l 
    const float FadeInAddScale;
    // �t�F�[�h�A�E�g���̖��t���[������scale�l 
    const float FadeOutAddScale;
    // ���t���[������Alpha�l
    const float AddAlpha;
    // ���t���[������Alpha�l
    const float SubAlpha;
    // Alpha�l�̍ő�l
    const float MaxAlpha;
    // �t�F�[�h�A�E�g����Ƃ��̑��x�̒萔
    const float VelocityAtFadeOut;

    // �t�F�[�h�A�E�g�ɐ؂�ւ���^�C�~���O�萔
    const int ChangeFadeOutTime;

};

