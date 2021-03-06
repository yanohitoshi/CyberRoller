#pragma once

#include "ParticleEffectBase.h"
/*
@file SwitchParticleEffect.h
@brief SwitchParticleEffect�̐����ƍX�V���s��
*/
class SwitchParticleEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�|�W�V����
    @param	�ړ����x
    */
    SwitchParticleEffect(const Vector3& _pos, const Vector3& _velocity);
    ~SwitchParticleEffect()override;
    
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
    float speed;
};

