#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

// �N���X�̑O���錾
class ExplosionObjectBase;

/*
@file ExplosionObjectEffectManager.h
@brief �������̃G�t�F�N�g�̐������s��
*/
class ExplosionObjectEffectManager :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	_owner �e�N���X�̃|�C���^
    */
    ExplosionObjectEffectManager(ExplosionObjectBase* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~ExplosionObjectEffectManager()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    /*
    @fn �G�t�F�N�g���A�N�e�B�u���̏����֐�
    */
    void ActiveEffect();

    /*
    @fn �����G�t�F�N�g���Y�����֐�
    */
    void GenerateExplosionEffectProcess();

    // �e��GameObject�ۑ��p�ϐ�
    ExplosionObjectBase* owner;

    // particle�̏�ԊǗ��p�ϐ�
    ParticleState particleState;

    // �����_���Ȓl�𐶐�����ۂɂ�����␳
    const float CorrectionRandValue;
    // �����_���Ȓl�ɑ΂��čŌ�ɂ�����␳�l
    const float LastCorrection;

    // 1�x�ɐ������锚���G�t�F�N�g�̐�
    const int MaxExplosionEffects;
    // �����_���͈̔�
    const int RandValue;
    // �g��G�t�F�N�g�̍ő吔
    const int MaxRipplesEffect;

    // ��������G�t�F�N�g�̃|�W�V����
    Vector3 effectPosition;
    // ��������G�t�F�N�g�̑��x
    Vector3 effectVelocity;
    // 1�x������������p�̐����t���O�ϐ�
    bool generateExplosionEffectsFlag;

    // 2�̔{���̎��Ƀt���[���J�E���g�Ɣ�r���邽�߂̒萔
    const int TowFrequency;
    // 3�̔{���̎��Ƀt���[���J�E���g�Ɣ�r���邽�߂̒萔
    const int ThreeFrequency;
};