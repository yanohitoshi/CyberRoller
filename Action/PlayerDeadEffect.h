#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

/*
@file PlayerDeadEffect.h
@brief ���S�G�t�F�N�g�̍X�V���s���N���X
*/
class PlayerDeadEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�e�ƂȂ�N���X�̃|�C���^
    @param	�|�W�V����
    @param	�v���C���[�̑̂Ɉʒu�����킹�邽�߂̊Ԋu
    */
    PlayerDeadEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _distance);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~PlayerDeadEffect()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    /*
    @fn �G�t�F�N�g�̉�]�����֐�
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
