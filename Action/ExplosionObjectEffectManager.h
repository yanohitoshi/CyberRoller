#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

class ExplosionObject;

class ExplosionObjectEffectManager :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	_owner �e�N���X�̃|�C���^
    */
    ExplosionObjectEffectManager(ExplosionObject* _owner);

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
    void ActiveEffectProcess();

    /*
    @fn �G�t�F�N�g���Y�����֐�
    */
    void GenerateEffectProcess();

    /*
    @fn �����G�t�F�N�g���Y�����֐�
    */
    void GenerateExplosionEffectProcess();

    // �e��GameObject�ۑ��p�ϐ�
    ExplosionObject* owner;

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

    Vector3 effectPosition;
    Vector3 effectVelocity;
    // 1�x������������p�̐����t���O�ϐ�
    bool generateExplosionEffectsFlag;
    //// �G�t�F�N�g���L��������Ă���̃t���[���𑪂�
    //int effectFrameCount;
};