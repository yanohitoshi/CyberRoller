#pragma once
#include "GameObject.h"
#include "ParticleEffectBase.h"

class PlayerTransformEffectManager :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	_owner �e�N���X�̃|�C���^
    */
    PlayerTransformEffectManager(PlayerObject* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~PlayerTransformEffectManager()override;

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
    PlayerObject* owner;
    // particle�̏�ԊǗ��p�ϐ�
    ParticleState particleState;
    // ��������G�t�F�N�g�̃|�W�V����
    Vector3 effectPosition;
    int frameCount;
    int effectCount;
    // ��x�ɐ�������G�t�F�N�g�̍ő吔
    const int MaxEffects;
    // �����_���͈̔͂̊���
    const int RandValue;
    // 1�x������������p�̐����t���O�ϐ�
    bool generateFlag;
};
