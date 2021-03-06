#pragma once

#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file PlayerSandSmokeMakeManeger.h
@brief PlayerSandSmokeMakeManeger�̐����ƍX�V���s��
*/
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
    @param	�Ō�̃t���[������������̂ɗv��������
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    ParticleState particleState;
    Vector3 effectPosition;
    int frameCount;
    int generateCount;

};

