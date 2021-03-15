#pragma once

#include "GameObject.h"
#include "ParticleEffectBase.h"

/*
@file PlayerSandSmokeMakeManeger.h
@brief PlayerSandSmokeMakeManeger�̐����ƍX�V���s��
*/
class PlayerSandSmokeMakeManeger :
    public GameObject
{
public:
    
    /*
    @fn �R���X�g���N�^
    @param	_owner �e�N���X�̃|�C���^
    */
    PlayerSandSmokeMakeManeger(GameObject* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~PlayerSandSmokeMakeManeger()override;

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
    // �A�j���[�V�����ɍ��킹�ēy���̈ʒu�����炷�p�̃|�W�V�����ϐ�
    Vector3 effectPosition;
    // �t���[���J�E���g�p�ϐ�
    int frameCount;
    // �����������𐔂��Ă��炷���������߂邽�߂̃J�E���g
    int generateCount;

};

