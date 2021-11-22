#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

/*
@file JumpAttackEffect.h
@brief �W�����v�U�����̃G�t�F�N�g�̍X�V���s���N���X
*/
class JumpAttackEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�|�W�V����
    @param	�ړ����x
    */
    JumpAttackEffect(const Vector3& _pos, const Vector3& _velocity);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~JumpAttackEffect()override;

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

    // alpha�l�̏����l
    const float InitAlpha;
    // scale�l�̏����l
    const float InitScale;
};

