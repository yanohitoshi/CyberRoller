#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file SandSmokeMakeManeger.h
@brief SandSmokeMakeManeger�̐������s��
*/
class SandSmokeMakeManeger :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�e�N���X�̃|�C���^
    */
    SandSmokeMakeManeger(GameObject* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~SandSmokeMakeManeger()override;
    
    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    /*
    @fn �傫���ǂ̃G�t�F�N�g���A�N�e�B�u�̎��̏����֐�
    */
    void ActiveBigWallEffectProcess();
    
    /*
    @fn �傫���ǂ̃G�t�F�N�g���Y�����֐�
    */
    void GenerateBigWallEffectProcess();

    /*
    @fn �������ǂ̃G�t�F�N�g���A�N�e�B�u�̎��̏����֐�
    */
    void ActiveSmallWallEffectProcess();

    /*
    @fn �������ǂ̃G�t�F�N�g���Y�����֐�
    */
    void GenerateSmallWallEffectProcess();

    // �e��GameObject�ۑ��p�ϐ�
    GameObject* owner;
    // particle�̏�ԊǗ��p�ϐ�
    ParticleState particleState;
    // �t���[���J�E���g�p�ϐ�
    int frameCount;
    // �e�ƂȂ铮���ǂ̃T�C�Y�����Ăǂꂭ�炢�̕���effect���o�������߂�p�̕ϐ�
    Vector3 ownerSize;

    // �傫���T�C�Y�̓����ǂ��ǂ���
    bool isBigWall;

    // ���x�̍Œ�l
    const Vector3 LowestVelValue;

    // �|�W�V����X�����炷�l
    const float ShiftPositionX;
    // �傫���ǂ̎��̃|�W�V����Y�����炷�l
    const float MaxShiftPositionY;
    // �傫���ǂ̎��̃|�W�V����Y�����炷�l
    const float MinShiftPositionY;
    // �傫���ǂ̃T�C�Y
    const float BigWallSize;
    // �������ǂ̃T�C�Y
    const float SmallWallSize;
    // �����_���Ȓl�𐶐�����ۂɂ�����␳
    const float CorrectionRandValue;
    // �����_���Ȓl�ɑ΂��čŌ�ɂ�����␳�l
    const float LastCorrection;

    // �����_���͈̔͂̊���X
    const int RandValueX;
    // �傫���ǂ̃����_���͈̔͂̊���Y
    const int BigRandValueY;
    // �������ǃ����_���͈̔͂̊���Y
    const int SmallRandValueY;
    // �����_���͈̔͂̊���Z
    const int RandValueZ;
    // ��������p�x�i�t���[���Ŕ�r�j
    const int GenerateFrequency;
    // �傫���ǂ̏ꍇ��1�x�ɐ�������G�t�F�N�g�̐�
    const int SmallWallMaxEffect;
    // �������ǂ̏ꍇ��1�x�ɐ�������G�t�F�N�g�̐�
    const int BigWallMaxEffect;
};

