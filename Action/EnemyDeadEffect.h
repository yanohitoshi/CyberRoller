#pragma once
#include "ParticleEffectBase.h"

class EnemyObjectBase;

class EnemyDeadEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�|�W�V����
    @param	�ړ����x
    */
    EnemyDeadEffect(GameObject* _owner,const Vector3& _pos);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~EnemyDeadEffect()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    /*
    @fn ��]�����֐�
    @brief	�G�t�F�N�g�̉�]���s��
    */
    void RotateEffect();

    // ���t���[������scale�l 
    const float AddScale;
    // ���t���[������alpha�l
    const float SubAlpha;
    // �����_���Ȓl�͈̔�
    const int RandValue;

    const Vector3 EffectColor;

};

