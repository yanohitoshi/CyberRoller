#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"
#include "CrystalEffectManager.h"

/*
@file CrystalDefaultEffect.h
@brief �N���X�^���̃G�t�F�N�g�̍X�V���s��
*/
class CrystalDefaultEffect :
    public ParticleEffectBase
{
public:
    
    /*
    @fn �R���X�g���N�^
    @param	�|�W�V����
    @param	�ړ����x
    @param	���F������pTag
    */
    CrystalDefaultEffect(const Vector3& _pos, const Vector3& _velocity,CrystalColor _crystalColor);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~CrystalDefaultEffect()override;
    
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

    // �t�F�[�h�C���t���O�ϐ�
    bool inFlag;

    // alpha�l�̍ő�l
    const float MaxAlphaValue;

    // ���t���[������scale�l 
    const float AddScale;
    // ���t���[������Alpha�l
    const float AddAlpha;
    // ���t���[������Alpha�l
    const float SubAlpha;
};

