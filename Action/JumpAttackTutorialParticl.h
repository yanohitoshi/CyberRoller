#pragma once
#include "ParticleEffectBase.h"

class JumpAttackTutorialParticl :
    public ParticleEffectBase
{
public:

    /*
    @brief	�R���X�g���N�^
    @param	�|�W�V����
    */
    JumpAttackTutorialParticl(const Vector3& _pos);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~JumpAttackTutorialParticl()override;

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

