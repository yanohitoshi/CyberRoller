#pragma once

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
    GameObject* owner;
    bool inFlag;
    float mScale;
    float mAlpha;
    float speed;
};

