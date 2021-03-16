#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file SwitchEffectMakeManeger.h
@brief SwitchEffectMakeManeger�̐����ƍX�V���s��
*/
class SwitchEffectMakeManeger :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�e�N���X�̃|�C���^
    */
    SwitchEffectMakeManeger(GameObject* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~SwitchEffectMakeManeger()override;
    
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
    // switch��ON�ɂȂ������ǂ����t���O
    bool ChackOnFlag;
    // �O�̃t���[���̃X�C�b�`�̏�Ԃ�ۑ�����p�t���O�ϐ�
    bool tmpChackOnFlag;
    // 1�x������������p�̐����t���O�ϐ�
    bool generateFlag;

};

