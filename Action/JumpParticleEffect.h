#pragma once
#include "ParticleEffectBase.h"

/*
@file JumpParticleEffect.h
@brief JumpParticleEffect�̐����ƍX�V���s��
*/
class JumpParticleEffect :
    public ParticleEffectBase
{
public:
    
    /*
    @fn �R���X�g���N�^
    @param	�|�W�V����
    @param	�ړ����x
    */
    JumpParticleEffect(const Vector3& _pos, const Vector3& _velocity);
    ~JumpParticleEffect()override;
    
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

