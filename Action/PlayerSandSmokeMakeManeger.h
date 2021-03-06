#pragma once

#include "GameObject.h"
#include "ParticleEffectBase.h"

class PlayerSandSmokeMakeManeger :
    public GameObject
{
public:
    
    /*
    @fn �R���X�g���N�^
    @param	�e�N���X�̃|�C���^
    */
    PlayerSandSmokeMakeManeger(GameObject* _owner);
    ~PlayerSandSmokeMakeManeger()override;

    /*
    @fn �X�V����
    @param	�t���[�����[�g�Œ�pdeltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    ParticleState particleState;
    Vector3 effectPosition;
    int frameCount;
    int generateCount;

};

