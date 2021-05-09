#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

/*
@file TutorialSwitchOkEffect.h
@brief OK��Ԃ̃X�C�b�`�̃`���[�g���A���`����s��
*/
class TutorialSwitchOkEffect :
    public ParticleEffectBase
{
public:
    
    /*
    @brief	�R���X�g���N�^
    @param	�|�W�V����
    @param	�I�[�i�[�ƂȂ�GameObject�^�|�C���^
    */
    TutorialSwitchOkEffect(const Vector3& _pos, GameObject* _owner);
    
    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~TutorialSwitchOkEffect()override;

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

