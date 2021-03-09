#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file SandSmokeMakeManeger.h
@brief SandSmokeMakeManeger�̐����ƍX�V���s��
*/
class SandSmokeMakeManeger :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�e�N���X�̃|�C���^
    */
    SandSmokeMakeManeger(GameObject* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~SandSmokeMakeManeger()override;
    
    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    ParticleState particleState;
    int frameCount;
    Vector3 ownerSize;
};

