#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

class EnemyObjectBase;

class EnemyDeadEffectManager :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	_owner �e�N���X�̃|�C���^
    */
    EnemyDeadEffectManager(EnemyObjectBase* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~EnemyDeadEffectManager()override;

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

    // �e��GameObject�ۑ��p�ϐ�
    EnemyObjectBase* owner;
    // particle�̏�ԊǗ��p�ϐ�
    ParticleState particleState;
    // 1�x�ɐ�������G�t�F�N�g�̐�
    const int MaxEffects;
    // 1�x�ɐ�������G�t�F�N�g�̐�
    const int MaxExplosionEffects;
    // 1�x������������p�̐����t���O�ϐ�
    bool generateExplosionEffectsFlag;
    int frameCount;

    // �����_���Ȓl�𐶐�����ۂɂ�����␳
    const float CorrectionRandValue;
    // �����_���Ȓl�ɑ΂��čŌ�ɂ�����␳�l
    const float LastCorrection;
    const int RandValueX;
    const int RandValueY;
    const int RandValueZ;
};

