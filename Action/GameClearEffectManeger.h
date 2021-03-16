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
    // 1�x������������p�̐����t���O�ϐ�
    int generateCount;
    // ����������particle�̐��𐔂���ϐ�
    int particleCount;
};

