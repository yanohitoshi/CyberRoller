#pragma once

#include "GameObject.h"
#include "ParticleEffectBase.h"
#include "CrystalEffectManager.h"

/*
@file FireWorksEffectManeger.h
@brief FireWorksEffectManeger�̐����ƍX�V���s��
*/
class FireWorksEffectManeger :
    public GameObject
{
public:
    /*
    @fn �R���X�g���N�^
    @param	�e�N���X�̃|�C���^
    */
    FireWorksEffectManeger(GameObject* _owner);
    ~FireWorksEffectManeger()override;
    
    /*
    @fn �X�V����
    @param	�Ō�̃t���[������������̂ɗv��������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    GameObject* owner;
    ParticleState particleState;
    CrystalColor crystalColor;
    int frameCount;
    bool generateFlag;
    int particleCount;
};

