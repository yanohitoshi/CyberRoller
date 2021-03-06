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
    ~CrystalDefaultEffect()override;
    
    /*
    @fn �X�V����
    @param	�Ō�̃t���[������������̂ɗv��������
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    float mScale;
    float mAlpha;
    bool inFlag;
};

