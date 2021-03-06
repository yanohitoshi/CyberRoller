#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file LandingEffectManeger.h
@brief LandingEffectManeger�̐����ƍX�V���s��
*/
class LandingEffectManeger :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�e�N���X�̃|�C���^
    */
    LandingEffectManeger(GameObject* _owner);
    ~LandingEffectManeger()override;
    
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

