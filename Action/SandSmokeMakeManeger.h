#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"
class SandSmokeMakeManeger :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�e�N���X�̃|�C���^
    */
    SandSmokeMakeManeger(GameObject* _owner);
    ~SandSmokeMakeManeger()override;
    
    /*
    @fn �X�V����
    @param	�t���[�����[�g�Œ�pdeltaTime
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    ParticleState particleState;
    int frameCount;
    Vector3 ownerSize;
};

