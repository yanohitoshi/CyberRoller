#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
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
    
    /*
    @fn �G�t�F�N�g�̐����֐�
    */
    void CreateEffect();
    
    /*
    @fn �G�t�F�N�g�̃|�W�V�������E�ɂ��炷�֐�
    */
    void ShiftRightEffectPosition();

    /*
    @fn �G�t�F�N�g�̃|�W�V���������ɂ��炷�֐�
    */
    void ShiftLeftEffectPosition();

    // �e��GameObject�ۑ��p�ϐ�
    GameObject* owner;
    // particle�̏�ԊǗ��p�ϐ�
    ParticleState particleState;
    // �A�j���[�V�����ɍ��킹�ēy���̈ʒu�����炷�p�̃|�W�V�����ϐ�
    Vector3 effectPosition;
    // �t���[���J�E���g�p�ϐ�
    int frameCount;
    // �����������𐔂��邽�߂̃J�E���g
    int generateCount;
    // owner�̑��x�����ȏ�̏ꍇ�ɐ������邽�߂̒萔
    const float GenerateSpeedValue;
    // ��������o�Ă���悤�Ɍ����邽�߂ɂ��炷�l
    const float ShiftPositionValue;

};

