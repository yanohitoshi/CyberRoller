#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

/*
@file PlayerKnockBackEffect.h
@brief �m�b�N�o�b�N�G�t�F�N�g�̍X�V���s���N���X
*/
class PlayerKnockBackEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�e�N���X�̃|�C���^
    @param	�ړ����x
    @param	�v���C���[�̑̂Ɉʒu�����킹�邽�߂̊Ԋu
    */
    PlayerKnockBackEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _distance);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~PlayerKnockBackEffect()override;

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

