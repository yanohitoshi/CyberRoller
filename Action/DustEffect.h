#pragma once
#include "ParticleEffectBase.h"

class DustEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�e�ƂȂ�N���X�̃|�C���^
    @param	�|�W�V����
    @param	�ړ����x
    */
    DustEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _velocity);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~DustEffect()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // ���t���[������scale�l 
    const float AddScale;
    // ���t���[������alpha�l
    const float SubAlpha;
    // �G�t�F�N�g�̐F
    const Vector3 EffectColor;
};

