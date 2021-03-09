#pragma once
#include "ParticleEffectBase.h"

/*
@file PlayerSandSmokeEffect.h
@brief PlayerSandSmokeEffect�̐����ƍX�V���s��
*/
class PlayerSandSmokeEffect :
    public ParticleEffectBase
{
public:
    
    /*
    @fn �R���X�g���N�^
    @param	�|�W�V����
    @param	�ړ����x
    @param  �����Ԃ�����t���O
    */
    PlayerSandSmokeEffect(const Vector3& _pos, const Vector3& _velocity, bool _run);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~PlayerSandSmokeEffect()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    GameObject* owner;
    float mScale;
    float mAlpha;
    bool runFlag;

};

