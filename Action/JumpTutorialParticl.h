#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

/*
@file JumpTutorialParticl.h
@brief �W�����v�p�`���[�g���A����ParticlEffect�\�����s��
*/
class JumpTutorialParticl :
    public ParticleEffectBase
{
public:

    /*
    @brief	�R���X�g���N�^
    @param	�|�W�V����
    */
    JumpTutorialParticl(const Vector3& _pos);
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~JumpTutorialParticl()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �g��k���l�̏������萔
    const float InitScale;

};

