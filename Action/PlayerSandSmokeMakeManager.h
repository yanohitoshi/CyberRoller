#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "ParticleEffectBase.h"

enum class PlayerState;

/*
@file PlayerSandSmokeMakeManeger.h
@brief �v���C���[�̓y��(����)�̐������s��
*/
class PlayerSandSmokeMakeManager :
    public GameObject
{
public:
    
    /*
    @fn �R���X�g���N�^
    @param	_owner �e�N���X�̃|�C���^
    */
    PlayerSandSmokeMakeManager(PlayerObject* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~PlayerSandSmokeMakeManager()override;

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
    @fn �G�t�F�N�g�̃|�W�V�������E�ɂ��炷�֐�
    */
    void ShiftRightEffectPosition();

    /*
    @fn �G�t�F�N�g�̃|�W�V���������ɂ��炷�֐�
    */
    void ShiftLeftEffectPosition();

    // �e��GameObject�ۑ��p�ϐ�
    PlayerObject* owner;
    PlayerState ownerState;
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

