#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file LandingEffectManeger.h
@brief LandingEffectManeger�̐������s��
*/
class LandingEffectManager :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	_owner �e�N���X�̃|�C���^
    */
    LandingEffectManager(PlayerObject* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~LandingEffectManager()override;
    
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
    @fn �G�t�F�N�g���΂������v�Z�����֐�
    */
    void CalculatingDirectionProcess(int _index, Vector3& _velocity);

    // �e��GameObject�ۑ��p�ϐ�
    PlayerObject* owner;
    // particle�̏�ԊǗ��p�ϐ�
    ParticleState particleState;
    // 1�x������������p�̐����t���O�ϐ�
    bool generateEffectsFlag;
    // �v���C���[��Z���̈ړ��ʂ�ۑ����邽�߂̕ϐ�
    float tmpVelZ;
    // 1�x�ɐ�������G�t�F�N�g�̐�
    const int MaxEffects;
};

