#pragma once

#include "GameObject.h"
#include "ParticleEffectBase.h"
#include "CrystalEffectManager.h"

/*
@file FireWorksEffectManeger.h
@brief FireWorksEffectManeger�̐����ƍX�V���s��
*/
class FireWorksEffectManeger :
    public GameObject
{
public:
    /*
    @fn �R���X�g���N�^
    @param	_owner �e�N���X�̃|�C���^
    */
    FireWorksEffectManeger(GameObject* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~FireWorksEffectManeger()override;
    
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
    int frameCount;
    // 1�x������������p�̐����t���O�ϐ�
    bool generateFlag;
    // ����������particle�̐��𐔂���ϐ�
    int particleCount;
};

