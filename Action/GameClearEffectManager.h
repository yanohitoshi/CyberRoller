#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file GameClearEffectManeger.h
@brief �N���A���̃G�t�F�N�g�̐������s��
*/
class GameClearEffectManager :
    public GameObject
{
public:
    
    /*
    @fn �R���X�g���N�^
    @param	_owner �e�N���X�̃|�C���^
    */
    GameClearEffectManager(GameObject* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~GameClearEffectManager()override;
    
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
    @fn �G�t�F�N�g���΂������v�Z�����֐�
    @param _index���ڂ̃G�t�F�N�g��
    @param _velocity ���x
    */
    void CalculatingDirectionProcess(int _index, Vector3& _velocity);
    
    // �e��GameObject�ۑ��p�ϐ�
    GameObject* owner;
    // particle�̏�ԊǗ��p�ϐ�
    ParticleState particleState;
    // �t���[���J�E���g�p�ϐ�
    int frameCount;
    // �����������[�v�̉񐔂��J�E���g����p�̐����J�E���g�ϐ�
    int generateCount;
    // �������J�n���鍂��
    const float GenerateHeight;
    // �����_���̒l��␳����l
    const float SecondCorrectionValue;
    // �����_���Ȓl�𐶐�����ۂɂ�����␳
    const float CorrectionRandValue;
    // �����_���Ȓl�ɑ΂��čŌ�ɂ�����␳�l
    const float LastCorrection;
    // �����_���͈̔͂̊���
    const int RandValue;
    // 1�x�ɐ�������G�t�F�N�g�̐�
    const int MaxEffects;
    // ���̃G�t�F�N�g�A�N�e�B�u�Ő������[�v���񂷉�
    const int MaxGenerateCount;
    // ��������p�x�i�t���[���Ŕ�r�j
    const int GenerateFrequency;

};

