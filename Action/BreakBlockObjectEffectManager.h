#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

class BreakBlockObject;

class BreakBlockObjectEffectManager :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	_owner �e�N���X�̃|�C���^
    */
    BreakBlockObjectEffectManager(BreakBlockObject* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~BreakBlockObjectEffectManager()override;

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
    BreakBlockObject* owner;

    // particle�̏�ԊǗ��p�ϐ�
    ParticleState particleState;

    Vector3 effectPosition;
    Vector3 effectVelocity;
    // 1�x������������p�̐����t���O�ϐ�
    bool generateExplosionEffectsFlag;
};

