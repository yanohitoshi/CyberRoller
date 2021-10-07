#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

// �N���X�̑O���錾
class EnemyObjectBase;

/*
@file EnemyElectricShockEffect.h
@brief �d���G�t�F�N�g�̍X�V���s���N���X
*/
class EnemyElectricShockEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�e�ƂȂ�N���X�̃|�C���^
    @param	�|�W�V����
    */
    EnemyElectricShockEffect(GameObject* _owner,const Vector3& _pos);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~EnemyElectricShockEffect()override;

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
  
    /*
    @fn ��]�v�Z����
    @param _axis ��]��
    */
    void Rotation(const Vector3 _axis);

    // ���t���[������scale�l 
    const float AddScale;
    // ���t���[������alpha�l
    const float SubAlpha;
    // �����_���Ȓl�͈̔�
    const int RandValue;
    // �G�t�F�N�g�̐F 
    const Vector3 EffectColor;

};

