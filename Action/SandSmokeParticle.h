#pragma once

#include "ParticleEffectBase.h"
/*
@file SandSmokeParticle.h
@brief SandSmokeParticle�̐����ƍX�V���s��
*/
class SandSmokeParticle :
    public ParticleEffectBase
{
public:
    
    /*
    @fn �R���X�g���N�^
    @param	�|�W�V����
    @param	�ړ����x
    */
    SandSmokeParticle(const Vector3& _pos, const Vector3& _velocity);
    ~SandSmokeParticle()override;
    
    /*
    @fn �X�V����
    @param	�Ō�̃t���[������������̂ɗv��������
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    float mScale;
    float mAlpha;

};

