#pragma once
#include "ParticleEffectBase.h"

/*
@file LandingEffect.h
@brief LandingEffect�̐����ƍX�V���s��
*/
class LandingEffect :
    public ParticleEffectBase
{
public:
    
    /*
    @fn �R���X�g���N�^
    @param	�|�W�V����
    @param	�ړ����x
    */
    LandingEffect(const Vector3& _pos, const Vector3& _velocity);
    ~LandingEffect()override;

    /*
    @fn �X�V����
    @param	�Ō�̃t���[������������̂ɗv��������
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    ParticleState particleState;
    GameObject* owner;
    float mScale;
    float mAlpha;
    bool ChackOnFlag;
    bool tmpChackOnFlag;
    bool generateFlag;

};

