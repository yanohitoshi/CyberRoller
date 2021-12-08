#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file PlayerAttackHitEffectManager.h
@brief �v���C���[���G�l�~�[�ւ̍U���𐬌������Ƃ��̃G�t�F�N�g�̐������s���N���X
*/
class PlayerAttackHitEffectManager :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	_owner �e�N���X�̃|�C���^
    */
    PlayerAttackHitEffectManager(PlayerObject* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~PlayerAttackHitEffectManager()override;

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
    void ActiveEffect();

    /*
    @fn �G�t�F�N�g���Y�����֐�
    */
    void GenerateEffect();

    // �e��GameObject�ۑ��p�ϐ�
    PlayerObject* owner;
    // particle�̏�ԊǗ��p�ϐ�
    ParticleState particleState;
    // ��������G�t�F�N�g�̃|�W�V����
    Vector3 effectPosition;
    // �|�W�V������␳����l
    const float CorrectionPosition;
    // 1�x������������p�̐����t���O�ϐ�
    bool generateFlag;
};

