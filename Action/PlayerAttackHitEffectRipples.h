#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

/*
@file PlayerAttackHitEffectRipples.h
@brief �q�b�g�G�t�F�N�g(�g��)�̍X�V���s���N���X
*/
class PlayerAttackHitEffectRipples :
    public ParticleEffectBase
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�e�ƂȂ�N���X�̃|�C���^
    @param	�|�W�V����
    @param	�ړ����x
    */
    PlayerAttackHitEffectRipples(GameObject* _owner, const Vector3& _pos, const Vector3& _velocity);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~PlayerAttackHitEffectRipples()override;

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
    // �ړ����x�萔
    const float MoveSpeed;
};

