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
    @param	_owner �e�N���X�̃|�C���^
    */
    JumpParticleEffectManeger(GameObject* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~JumpParticleEffectManeger()override;
    
    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    GameObject* owner;
    ParticleState particleState;
    bool ChackOnFlag;
    float tmpVelZ;
    bool generateFlag;

};

