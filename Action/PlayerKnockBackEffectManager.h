#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file PlayerKnockBackEffectManager.h
@brief �m�b�N�o�b�N�G�t�F�N�g�̐������s���N���X
*/
class PlayerKnockBackEffectManager :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	_owner �e�N���X�̃|�C���^
    */
    PlayerKnockBackEffectManager(PlayerObject* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~PlayerKnockBackEffectManager()override;

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
    // �Ԋu
    Vector3 distance;
    // �G�t�F�N�g�𐶐����鎞�Ԃ𐔂���
    int effectFrameCount;
    // �|�W�V���������炷���߂̃I�t�Z�b�g
    const float PositionOffset;
};

