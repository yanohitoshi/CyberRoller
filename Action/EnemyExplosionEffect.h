#pragma once
#include "ParticleEffectBase.h"

class EnemyObjectBase;

class EnemyExplosionEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�|�W�V����
    @param	�ړ����x
    */
    EnemyExplosionEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _velocity);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~EnemyExplosionEffect()override;

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

    const Vector3 EffectColor;

    // �G�t�F�N�g���������鎞�Ԃ��J�E���g����
    int enableCount;
    // �G�t�F�N�g���������鎞��
    const int EnableTime;
    // �����������ǂ���
    bool isEnabled;
};

