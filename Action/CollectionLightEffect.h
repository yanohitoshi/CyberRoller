#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ParticleEffectBase.h"

// �N���X�̑O���錾
enum CrystalColor;

/*
@file CollectionLightEffect.h
@brief ���G�t�F�N�g�̍X�V���s��
*/
class CollectionLightEffect :
    public ParticleEffectBase
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�e�ƂȂ�N���X�̃|�C���^
    @param	�|�W�V����
    @param	�ړ����x
    */
    CollectionLightEffect(GameObject* _owner, const Vector3& _pos, const Vector3& _direction,CrystalColor _crystalColor);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~CollectionLightEffect()override;

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
    // �����x�N�g��
    Vector3 direction;
    // �T�C���֐��ɓn���l
    float value;
    // �T�C���֐��ɑ����l 
    const float AddValue;
    // �T�C���֐�����Ԃ��Ă����l
    float sinV;
    // alpha�l�̏����l
    const float InitAlpha;
    // scale�l�̏����l
    const float InitScale;

    // �����_���ȑ��x�𓾂邽�߂̒萔
    const int SpeedRandValue;
    // �����_���ȑ��x�̍Œ�l
    const int SpeedLowestValue;
    // �����_����Sin�֐��ɓn���l�𓾂邽�߂̒萔
    const int SinRandValue;
};

