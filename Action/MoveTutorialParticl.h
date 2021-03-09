#pragma once
#include "ParticleEffectBase.h"

/*
@file MoveTutorialParticl.h
@brief �ړ��p�`���[�g���A����ParticlEffect�̕\�����s��
*/
class MoveTutorialParticl :
    public ParticleEffectBase
{
public:
    
    /*
    @brief	�R���X�g���N�^
    @param	�|�W�V����
    */
    MoveTutorialParticl(const Vector3& _pos);
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~MoveTutorialParticl()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:
};

