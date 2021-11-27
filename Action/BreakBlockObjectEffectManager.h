#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

// �N���X�̑O���錾
class BreakBlockObject;

/*
@file BreakBlockObjectEffectManager.h
@brief ����u���b�N�̃G�t�F�N�g�̐������s��
*/
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
    @fn �y���G�t�F�N�g���Y�����֐�
    */
    void GenerateDustEffectProcess();

    /*
    @fn �j�ЃG�t�F�N�g���Y�����֐�
    */
    void GenerateDebrisEffectProcess();

    // �e��GameObject�ۑ��p�ϐ�
    BreakBlockObject* owner;

    // particle�̏�ԊǗ��p�ϐ�
    ParticleState particleState;

    // 2�̔{���̎��Ƀt���[���J�E���g�Ɣ�r���邽�߂̒萔
    const int TowFrequency;
    // 3�̔{���̎��Ƀt���[���J�E���g�Ɣ�r���邽�߂̒萔
    const int ThreeFrequency;

    // ���G�t�F�N�g�̍ő吔
    const int DustMaxEffect;
    // ���p�̃����_���ɗp����l
    const int DustEffectRandValue;

    // �j�ЃG�t�F�N�g�̍ő吔
    const int DebrisMaxEffect;
    // �j�Зp�̃����_���ɗp����l
    const int DebrisEffectRandValue;

    // �����_���̒l�����ۂ̕␳�l
    const float CorrectionRandValue;
    // �����_���̒l�Ɋ|����Ō�̕␳�l
    const float LastCorrection;
    // Active�ɂȂ��Ă���̃J�E���g�𐔂���
    int activeCount;
    // �G�t�F�N�g�{�̂ɓn���|�W�V����
    Vector3 effectPosition;
    // �G�t�F�N�g�{�̂ɓn�����x
    Vector3 effectVelocity;
    // 1�x������������p�̐����t���O�ϐ�
    bool generateEffectsFlag;
};