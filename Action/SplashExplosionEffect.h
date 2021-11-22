#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

/*
@file SplashExplosionEffect.h
@brief �����̔򖗃G�t�F�N�g�̍X�V���s��
*/
class SplashExplosionEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�e�ƂȂ�N���X�̃|�C���^
    @param	�|�W�V����
    @param	�ړ����x
    */
    SplashExplosionEffect(const Vector3& _pos, const Vector3& _velocity);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~SplashExplosionEffect()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // ���t���[������scale�l 
    const float AddScale;
    // ���t���[������alpha�l
    const float SubAlpha;
    // �G�t�F�N�g�̐F
    const Vector3 EffectColor;
    // alpha�l�̏����l
    const float InitAlpha;
    // scale�l�̏����l
    const float InitScale;

    // �����_���ȑ��x�𓾂邽�߂̒l
    const int SpeedRandValue;
    // �����_���ȑ��x�̕␳�l
    const int SpeedCorrection;
};

