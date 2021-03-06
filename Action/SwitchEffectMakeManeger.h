#pragma once
#include "GameObject.h"

#include "ParticleEffectBase.h"

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
    @param	�t���[�����[�g�Œ�pdeltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    GameObject* owner;
    ParticleState particleState;
    bool ChackOnFlag;
    bool tmpChackOnFlag;
    bool generateFlag;

};

