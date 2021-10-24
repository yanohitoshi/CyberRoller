#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class SkeletalMeshComponent;
class Mesh;
class Animation;
class TitleJumpAttackPlayerObject;
class TitlePlayerStateBase;
enum class TitlePlayerState;

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
    @brief �X�e�[�g�v�[���p�}�b�v�ɃX�e�[�g�N���X��ǉ�����֐�
    @param	_state �ǉ�����X�e�[�g�N���X�̃|�C���^
    @param	_stateTag ���ƂȂ�^�O
    */
    void AddStatePoolMap(TitlePlayerStateBase* _state, TitlePlayerState _stateTag);

    /*
    @brief �X�e�[�g�v�[���p�}�b�v����X�e�[�g�N���X���폜����֐�
    @param	_stateTag ���ƂȂ�^�O
    */
    void RemoveStatePoolMap(TitlePlayerState _stateTag);

    /*
    @brief �X�e�[�g�v�[���p�}�b�v���N���A����
    */
    void ClearStatePoolMap();

    //3D���f���̕`����s���N���X
    SkeletalMeshComponent* skeltalMeshComponent;
    // Mesh�̓ǂݍ��݂��s���N���X
    Mesh* mesh;
    // �A�j���[�V�����pvector�z��
    std::vector<const Animation*> animTypes;

    // ���̃v���[���[��state��Ԃ�ۑ����邽�߂̕ϐ�
    TitlePlayerState nowState;
    // �ύX���ꂽ���̃v���[���[��state��Ԃ�ۑ����邽�߂̕ϐ�
    TitlePlayerState nextState;

    // �Sstate���i�[�����}�b�v
    std::unordered_map<TitlePlayerState, TitlePlayerStateBase*> statePoolMap;

    // �W�����v�A�^�b�N��Ԃ̃v���C���[�N���X�̃|�C���^
    TitleJumpAttackPlayerObject* titleJumpAttackPlayerObject;

    // �����|�W�V�����萔
    const Vector3 InitPosition;
    // �W�����v�t���O
    bool jumpFlag;
    // �W�����v�̊Ԋu�𑪂邽�߂̃J�E���g
    int jumpDelayCount;
    // �W�����v������
    int jumpCount;
    // ��p����W�����v��
    float jumpPower;
    // �W�����v���鎞�ԗp�J�E���g
    int jumpFrameCount;

    // ��]�p�萔
    const float RotationAngle;

public:

    /*
    @fn skeltalMeshComponent��getter�֐�
    @return SkeletalMeshComponent�@SkeletalMeshComponent�N���X�̃|�C���^��Ԃ�
    */
    SkeletalMeshComponent* GetSkeletalMeshComponent() { return skeltalMeshComponent; }

    /*
    @fn titleJumpAttackPlayerObject��getter�֐�
    @return titleJumpAttackPlayerObject�@titleJumpAttackPlayerObject�N���X�̃|�C���^��Ԃ�
    */
    TitleJumpAttackPlayerObject* GetTitleJumpAttackPlayerObject() { return titleJumpAttackPlayerObject; }

    /*
    @fn Animation��getter�֐�
    @param _state ���݂̃v���C���[�̃X�e�[�^�X
    @return Animation Animation�N���X�̃|�C���^��Ԃ�
    */
    const Animation* GetAnimation(TitlePlayerState _state);

    /*
    @fn InitPosition��getter�֐�
    @return InitPosition�@InitPosition��Ԃ�
    */
    Vector3 GetInitPosition() { return InitPosition; }

    /*
    @fn jumpFlag��getter�֐�
    @return jumpFlag�@jumpFlag��Ԃ�
    */
    bool GetJumpFlag() { return jumpFlag; }

    /*
    @fn jumpFrameCount��getter�֐�
    @return jumpFrameCount�@jumpFrameCount��Ԃ�
    */
    int GetJumpFrameCount() { return jumpFrameCount; }

    /*
    @fn jumpCount��getter�֐�
    @return jumpCount�@jumpCount��Ԃ�
    */
    int GetJumpCount() { return jumpCount; }

    /*
    @fn jumpPower��getter�֐�
    @return jumpPower�@jumpPower��Ԃ�
    */
    float GetJumpPower() { return jumpPower; }

    /*
    @fn jumpFlag��setter�֐�
    @param	bool _jumpFlag true:�W�����v�� false:�W�����v���łȂ�
    */
    void SetJumpFlag(bool _jumpFlag) { jumpFlag = _jumpFlag; }
    
    /*
    @fn jumpFrameCount��setter�֐�
    @param	int _jumpFrameCount �W�����v���̃J�E���g
    */
    void SetJumpFrameCount(int _jumpFrameCount) { jumpFrameCount = _jumpFrameCount; }
    
    /*
    @fn nextState��setter�֐�
    @param	int _jumpCount �W�����v������
    */
    void SetJumpCount(int _jumpCount) { jumpCount = _jumpCount; }
    
    /*
    @fn nextState��setter�֐�
    @param	float _jumpPower �W�����v��
    */
    void SetJumpPower(float _jumpPower) { jumpPower = _jumpPower; }
};

