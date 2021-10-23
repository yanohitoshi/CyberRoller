#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class SkeletalMeshComponent;
class MeshComponent;
class Mesh;
class Animation;
enum class TitlePlayerState;

///*
//@enum AnimState
//    �@�v���C���[�̃A�j���[�V�����̏��
//      �^�C�g���p
//*/
//enum TitlePlayerState
//{
//    // �A�C�h�����O���
//    IDLE,
//    // ������
//    RUN,
//    // �W�����v���[�v
//    JUMPLOOP,
//    // �W�����v�J�n
//    JUMPSTART,
//    // �W�����v�I��
//    JUMPEND,
//    // �W�����v�A�^�b�N
//    JUMPATTACK,
//    // ���X�e�[�^�X��
//    ITEMNUM
//};

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
    
    /*
    @fn ��]�����֐�
    */
    void RotationProcess(float _angle,Vector3 _axis);
    
private:


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

    // �Sstate���i�[�����}�b�v
    std::unordered_map<TitlePlayerState, TitlePlayerStateBase*> statePoolMap;

    //3D���f���̕`����s���N���X
    SkeletalMeshComponent* skeltalMeshComponent;
    // Mesh�̓ǂݍ��݂��s���N���X
    Mesh* mesh;
    // 3D���f���̕`����s���N���X
    MeshComponent* meshComponent;

    // �d�͒萔
    const float Gravity;
    // �ڒn�t���O
    bool onGround;
    // �W�����v�t���O
    bool jumpFlag;
    // �W�����v�̊Ԋu�𑪂邽�߂̃J�E���g
    int jumpDelayCount;
    // �W�����v������
    int jumpCount;
    // ��p����W�����v��
    float jumpPower;
    // ����
    const float FirstJumpPower;
    // �W�����v���鎞�ԗp�J�E���g
    float jumpFrameCount;
    float jumpAttackRotationAngle;

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

    // ��]�p�萔
    const float JumpAttackRotationAngle;

public:

    /*
    @fn skeltalMeshComponent��getter�֐�
    @return SkeletalMeshComponent�@SkeletalMeshComponent�N���X�̃|�C���^��Ԃ�
    */
    SkeletalMeshComponent* GetSkeletalMeshComponent() { return skeltalMeshComponent; }

    /*
    @fn meshComponent��getter�֐�
    @return meshComponent�@meshComponent�N���X�̃|�C���^��Ԃ�
    */
    MeshComponent* GetMeshComponent() { return meshComponent; }

    /*
    @fn Animation��getter�֐�
    @param _state ���݂̃v���C���[�̃X�e�[�^�X
    @return Animation Animation�N���X�̃|�C���^��Ԃ�
    */
    const Animation* GetAnimation(TitlePlayerState _state);

    bool GetJumpFlag() { return jumpFlag; }
    bool GetOnGroundFlag() { return onGround; }
    int GetJumpFrameCount() { return jumpFrameCount; }
    int GetJumpCount() { return jumpCount; }
    float GetJumpPower() { return jumpPower; }

    void SetJumpFlag(bool _jumpFlag) { jumpFlag = _jumpFlag; }
    void SetOnGround(bool _onGround) { onGround = _onGround; }
    void SetJumpFrameCount(int _jumpFrameCount) { jumpFrameCount = _jumpFrameCount; }
    void SetJumpCount(int _jumpCount) { jumpCount = _jumpCount; }
    void SetJumpPower(float _jumpPower) { jumpPower = _jumpPower; }
};

