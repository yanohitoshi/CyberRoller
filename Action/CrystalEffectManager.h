#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

class MoveWallBlock;

/*
@enum �N���X�^���peffect�̐F��Tag
*/
enum CrystalColor
{
    WHITE,
    RED,
    BLUE,
    GREEN,
};

/*
@file CrystalEffectManager.h
@brief CrystalEffectManager�̐����ƍX�V���s��
*/
class CrystalEffectManager :
    public GameObject
{
public:
    
    /*
    @fn �R���X�g���N�^
    @param	�e�N���X�̃|�C���^
    @param	���F������pTag
    */
    CrystalEffectManager(GameObject* _owner, CrystalColor _crystalColor, MoveWallBlock* _lastMoveWall);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~CrystalEffectManager()override;
    
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
    @fn �|�W�V�����̉�]�����֐�
    */
    void RotationProcess(float _deltaTime);

    MoveWallBlock* lastMoveWallBlock;

    // �e��GameObject�ۑ��p�ϐ�
    GameObject* owner;
    // particle�̏�ԊǗ��p�ϐ�
    ParticleState particleState;
    // �N���X�^��effect�̐F���Ǘ�����ϐ�
    CrystalColor crystalColor;
    // ��]������ۂ̈ꎞ�ۑ��p�ϐ�
    Vector3 tmpMovePos;
    // �t���[���J�E���g�p�ϐ�
    int frameCount;
    // effect�𔭐�������^�C�~���O�𑪂�J�E���g�ϐ�
    int activeFrameCount;
    // effect�𔭐������邩�ǂ���
    bool isEffectActive;
    // ��]�̔��a�ϐ�
    const float Radius;
    // ��]�ŗp���郈�[�̊p�x�ϐ�
    float yaw;
    // ��]���x
    const float YawSpeed;
    // Z���̃|�W�V���������炷�l
    const float ShiftPositionZ;
    // Z���݂̂ɓK��������␳�l
    const float SecondCorrectionValue;
    // �����_���Ȓl�𐶐�����ۂɂ�����␳
    const float CorrectionRandValue;
    // �����_���Ȓl�ɑ΂��čŌ�ɂ�����␳�l
    const float LastCorrection;
    // �����_���͈̔͂̊���
    const int RandValue;
    // �f���^�^�C���ɂ�����␳
    const float DeltaTimeCorrectionValue;

};

