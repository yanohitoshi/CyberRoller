#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"
#include "CrystalEffectManager.h"

/*
@file FierWorksEffect.h
@brief FierWorksEffect�̐����ƍX�V���s��
*/
class FierWorksEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�|�W�V����
    @param	�ړ����x
    @param	���F������pTag
    */
    FierWorksEffect(const Vector3& _pos, const Vector3& _velocity , CrystalColor _crystalColor);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~FierWorksEffect()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �e��GameObject�ۑ��p�ϐ�
    GameObject* owner;
    // �t�F�[�h�C���t���O
    bool inFlag;
    // �g��k���ϐ�
    float mScale;
    // �����x�ϐ�
    float mAlpha;
    // ���x�ϐ�
    float speed;
};

