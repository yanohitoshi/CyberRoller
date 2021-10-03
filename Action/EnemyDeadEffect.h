#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

// �N���X�̑O���錾
class EnemyObjectBase;

/*
@file EnemyDeadEffect.h
@brief EnemyDeadEffect�̍X�V���s���N���X
*/
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
    // �G�t�F�N�g�̐F 
    const Vector3 EffectColor;

};

