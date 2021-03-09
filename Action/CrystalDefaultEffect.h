#pragma once
#include "ParticleEffectBase.h"
#include "CrystalEffectManager.h"

/*
@file CrystalDefaultEffect.h
@brief CrystalDefaultEffect�̐����ƍX�V���s��
*/
class CrystalDefaultEffect :
    public ParticleEffectBase
{
public:
    
    /*
    @fn �R���X�g���N�^
    @param	�|�W�V����
    @param	�ړ����x
    @param	���F������pTag
    */
    CrystalDefaultEffect(const Vector3& _pos, const Vector3& _velocity,CrystalColor _crystalColor);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~CrystalDefaultEffect()override;
    
    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    float mScale;
    float mAlpha;
    bool inFlag;
};

