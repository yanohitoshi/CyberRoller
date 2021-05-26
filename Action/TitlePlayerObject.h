#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class SkeletalMeshComponent;
class Animation;

/*
@enum AnimState
    �@�v���C���[�̃A�j���[�V�����̏��
      �^�C�g���p
*/
enum TitleAnimState
{
    IDLE,
    WALK,
    RUN,
    JUMPLOOP,
    JUMPSTART,
    JUMPEND,
    DOWN,
    DOWN_LOOP,
    DOWN_UP,
    DOWN_OVER,
    PLAYER_DEAD,
    ITEMNUM
};

/*
@file TitlePlayerObject.h
@brief �^�C�g���V�[�����ł̃v���C���[
       �����A�j���[�V�������Đ����邾���̃N���X
*/
class TitlePlayerObject :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @param	�|�W�V����
    @param	�ė��p���邩�t���O
    @param	�I�u�W�F�N�g���ʗptag
    */
    TitlePlayerObject(const Vector3& _pos, bool _reUseGameObject, const Tag _objectTag);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~TitlePlayerObject()override;
    
    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;
    
private:

    /*
    @fn ��]�����֐�
    */
    void RotationProcess();

    /*
    @fn �d�͏����֐�
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void GravityProcess(float _deltaTime);

    /*
    @fn �W�����v�f�B���C�����֐�
    */
    void JumpDelayProcess();

    /*
    @fn �W�����v�����֐�
    */
    void JumpProcess();

    /*
    @fn �ڒn���菈���֐�
    */
    void IsGroundingProcess();

    /*
    @fn �A�j���[�V�����̍X�V����
    */
    void AnimationUpdate();

    // �A�j���[�V�����pvector�z��
    std::vector<const Animation*> animTypes;
    // �A�j���[�V�����̏�ԗp�ϐ�
    int animState;

    //3D���f���̕`����s���N���X
    SkeletalMeshComponent* skeltalMeshComponent;
    
    // �d�͒萔
    const float Gravity;
    // �ڒn�t���O
    bool onGround;
    // �W�����v�t���O
    bool jumpFlag;
    // �W�����v�̊Ԋu�𑪂邽�߂̃J�E���g
    int jumpDelayCount;
    // ��p����W�����v��
    float jumpPower;
    // ����
    float firstJumpPower;
    // �W�����v���鎞�ԗp�J�E���g
    float jumpFrameCount;

    // �������x�̍ő�l
    const float MaxFallSpeed;

    // �W�����v�𑱂���t���[���J�E���g�萔
    const float JumpLimitTime;

    // �W�����v����Ԋu�̎��Ԓ萔
    const int JumpDelayTime;

    // �W�����v�����x�萔
    const float JumpSpeed;

    // �ڒn����������W�l�萔
    const float OnGroundCoordinate;

    // ��]�p�萔
    const float RotationAngle;

};

