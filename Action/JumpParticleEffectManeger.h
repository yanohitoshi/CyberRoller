#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file JumpParticleEffectManeger.h
@brief JumpParticleEffectManeger�̐����ƍX�V���s��
*/
class JumpParticleEffectManeger :
    public GameObject
{
public:
    
    /*
    @fn �R���X�g���N�^
    @param	�e�N���X�̃|�C���^
    */
    JumpParticleEffectManeger(GameObject* _owner);
    ~JumpParticleEffectManeger()override;
    
    /*
    @fn �X�V����
    @param	�Ō�̃t���[������������̂ɗv��������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    GameObject* owner;
    ParticleState particleState;
    bool ChackOnFlag;
    float tmpVelZ;
    bool generateFlag;

};

