#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

/*
@file ExplosionRipplesEffect.h
@brief �����̔g��G�t�F�N�g�̍X�V���s��
*/
class ExplosionRipplesEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�e�ƂȂ�N���X�̃|�C���^
    @param	�|�W�V����
    */
    ExplosionRipplesEffect(GameObject* _owner, const Vector3& _pos);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~ExplosionRipplesEffect()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    /*
    @fn �G�t�F�N�g�̉�]����
    */
    void RotateEffect();

    // �p�x
    float angle;

    const int RandValue;
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
    // �����_���ȑ��x�̍Œ�l
    const int RotateLowestValue;
    // Y���̉�]�p�x
    const float AxisYAngle;
};

