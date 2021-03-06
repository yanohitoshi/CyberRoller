#pragma once
#include "GameObject.h"

#include "ParticleEffectBase.h"
/*
@file SwitchEffectMakeManeger.h
@brief SwitchEffectMakeManeger�̐����ƍX�V���s��
*/
class SwitchEffectMakeManeger :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�e�N���X�̃|�C���^
    */
    SwitchEffectMakeManeger(GameObject* _owner);
    ~SwitchEffectMakeManeger()override;
    
    /*
    @fn �X�V����
    @param	�Ō�̃t���[������������̂ɗv��������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    GameObject* owner;
    ParticleState particleState;
    bool ChackOnFlag;
    bool tmpChackOnFlag;
    bool generateFlag;

};

