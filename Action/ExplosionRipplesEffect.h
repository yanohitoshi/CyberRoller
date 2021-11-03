#pragma once
#include "ParticleEffectBase.h"

class ExplosionRipplesEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�e�ƂȂ�N���X�̃|�C���^
    @param	�|�W�V����
    @param	�ړ����x
    */
    ExplosionRipplesEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _velocity);

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


    void RotateEffect();

    float angle;

    const int RandValue;
    // ���t���[������scale�l 
    const float AddScale;
    // ���t���[������alpha�l
    const float SubAlpha;
    // �G�t�F�N�g�̐F
    const Vector3 EffectColor;
};

