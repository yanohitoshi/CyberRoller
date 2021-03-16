#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

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
    CrystalEffectManager(GameObject* _owner, CrystalColor _crystalColor);

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
    // �ړ������𔽓]�����邩�t���O�ϐ�
    bool revers;
    // ��]�̔��a�ϐ�
    float r;
    // ��]�ŗp���郈�[�̊p�x�ϐ�
    float yaw;
    // ��]���x
    const float yawSpeed = 0.06f;
};

