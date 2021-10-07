#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file PlayerDeadEffectManager.h
@brief ���S�G�t�F�N�g�̐������s���N���X
*/
class PlayerDeadEffectManager :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	_owner �e�N���X�̃|�C���^
    */
    PlayerDeadEffectManager(PlayerObject* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~PlayerDeadEffectManager()override;

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
    // �G�t�F�N�g�̈ʒu���v���C���[�̑̂ɍ��킹�邽�߂̊Ԋu
    Vector3 distance;
    // �G�t�F�N�g�̈ʒu���v���C���[�̑̂ɍ��킹�邽�߂̊Ԋu���v�Z���邽�߂̃I�t�Z�b�g�萔
    const float DistanceOffset;
    // ���S��ԂɂȂ��Ă���̎��Ԃ𐔂���
    int generationCount;
    // �G�t�F�N�g�𔭐������n�߂鎞��
    const int GenerationTime;
    // �G�t�F�N�g�𐶐����鎞�Ԃ𐔂���
    int effectFrameCount;
    // �|�W�V���������炷���߂̃I�t�Z�b�g
    const float PositionOffset;
    // z�����������炷���߂̒萔
    const float ShiftPositionZ;
};

