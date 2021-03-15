#pragma once
#include "ParticleEffectBase.h"

/*
@file JumpParticleEffect.h
@brief JumpParticleEffect�̐����ƍX�V���s��
*/
class JumpParticleEffect :
    public ParticleEffectBase
{
public:
    
    /*
    @fn �R���X�g���N�^
    @param	�|�W�V����
    @param	�ړ����x
    */
    JumpParticleEffect(const Vector3& _pos, const Vector3& _velocity);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~JumpParticleEffect()override;
    
    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    
    // particle�̃X�e�[�^�X�Ǘ��p�ϐ�
    ParticleState particleState;
    // �e��GameObject�ۑ��p�ϐ�
    GameObject* owner;
    // �g��k���ϐ�
    float mScale;
    // �����x�ϐ�
    float mAlpha;

};

