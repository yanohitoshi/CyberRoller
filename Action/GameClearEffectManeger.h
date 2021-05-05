#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file GameClearEffectManeger.h
@brief GameClearEffectManeger�̐����ƍX�V���s��
*/
class GameClearEffectManeger :
    public GameObject
{
public:
    
    /*
    @fn �R���X�g���N�^
    @param	_owner �e�N���X�̃|�C���^
    */
    GameClearEffectManeger(GameObject* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~GameClearEffectManeger()override;
    
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
    // �t���[���J�E���g�p�ϐ�
    int frameCount;
    // �����������[�v�̉񐔂��J�E���g����p�̐����J�E���g�ϐ�
    int generateCount;
    // �������J�n���鍂��
    const float GenerateHeight;
    // �����_���̒l��␳����l
    const float SecondCorrectionValue;
    // ���̂܂܈����ƒl���傫���Ȃ肷����̂ŕ␳�������邽�߂̒l
    const float CorrectionRandValue;
    // �����_���͈̔͂̊���
    const int RandValue;
    // 1�x�ɐ�������G�t�F�N�g�̐�
    const int MaxEffects;
    // ���̃G�t�F�N�g�A�N�e�B�u�Ő������[�v���񂷉�
    const int MaxGenerateCount;
    // ��������p�x�i�t���[���Ŕ�r�j
    const int GenerateFrequency;

};

