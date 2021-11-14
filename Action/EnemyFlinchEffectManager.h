#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

// �N���X�̑O���錾
class EnemyObjectBase;

class EnemyFlinchEffectManager :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	_owner �e�N���X�̃|�C���^
    */
    EnemyFlinchEffectManager(EnemyObjectBase* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~EnemyFlinchEffectManager()override;

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

    // �����_���Ȓl�𐶐�����ۂɂ�����␳
    const float CorrectionRandValue;
    // �����_���Ȓl�ɑ΂��čŌ�ɂ�����␳�l
    const float LastCorrection;

    // 1�x�ɐ������锚���G�t�F�N�g�̐�
    const int MaxExplosionEffects;
    // �����_���͈̔�
    const int RandValue;

    // �G�t�F�N�g���L��������Ă���̃t���[���𑪂�
    int effectFrameCount;
};
