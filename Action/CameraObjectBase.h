#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class CameraObjectStateBase;
enum class CameraState;

/*
@file CameraObjectBase.h
@brief GameObject���p�������J�����̊��N���X
*/
class CameraObjectBase :
    public GameObject
{

public:

    /*
    @fn �R���X�g���N�^
    @param	�ė��p���邩�t���O
    @param	ObjectTag
    */
    CameraObjectBase(bool _reUseGameObject, const Tag _objectTag);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~CameraObjectBase();

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    virtual void UpdateGameObject(float _deltaTime = 1.0f);

    /*
    @fn ���͊֐�
    @brief	���͏������s��
    @param	_keyState ���͏��
    */
    virtual void GameObjectInput(const InputState& _keyState);

    /*
    @brief ���X�|�[�������Ƃ��ɃJ�����̈ʒu��������ԂɃZ�b�g����֐�
    */
    void ResetCamera() { yaw = Math::ToRadians(180); pitch = Math::ToRadians(30); }

    /*
    @brief �X�e�[�g�v�[���p�}�b�v�ɃX�e�[�g�N���X��ǉ�����֐�
    @param	_state �ǉ�����X�e�[�g�N���X�̃|�C���^
    @param	_stateTag ���ƂȂ�^�O
    */
    void AddStatePoolMap(CameraObjectStateBase* _state, CameraState _stateTag);

    /*
    @brief �X�e�[�g�v�[���p�}�b�v����X�e�[�g�N���X���폜����֐�
    @param	_stateTag ���ƂȂ�^�O
    */
    void RemoveStatePoolMap(CameraState _stateTag);

    /*
    @brief �X�e�[�g�v�[���p�}�b�v���N���A����
    */
    void ClearStatePoolMap();

protected:

    // �ړ���position
    Vector3 tmpMovePos;
    Vector3 tmpPosition;
    // �Ǐ]��̃I�u�W�F�N�g���W
    Vector3 lerpObjectPos;
    // view�s��
    Matrix4 view;
    // �v���C���[�̃|�C���^��ێ����邽�߂̕ϐ�
    PlayerObject* playerObject;
    // ���`�ۊǎ��Ƀf���^�^�C����������Ƃ��p�̕␳�萔
    const float DeltaCorrection;
    // �J������]�v�Z�p�̃��[�ƃs�b�`
    float yaw;
    float pitch;

    // ��p��ύX���邩�ǂ���
    bool isChangeMode;

    // �Ԋu
    Vector3 offSetPosition;

    // ����camera��state��Ԃ�ۑ����邽�߂̕ϐ�
    CameraState nowState;
    // �ύX���ꂽ����camera��state��Ԃ�ۑ����邽�߂̕ϐ�
    CameraState nextState;

    // �Sstate���i�[�����}�b�v
    std::unordered_map<CameraState, CameraObjectStateBase*> statePoolMap;

public: // �Q�b�^�[�Z�b�^�[
    
    /*
    @brief �J�����̑O���x�N�g���𓾂邽�߂�getter
    @return �J�����̑O���x�N�g��
    */
    Vector3 GetCameraVec() const { return forwardVec; }

    /*
    @brief �Ǐ]����I�u�W�F�N�g�̃|�C���^�𓾂邽�߂�getter
    @return �Ǐ]����I�u�W�F�N�g�̃|�C���^
    */
    PlayerObject* GetLerpObject() const { return playerObject; }

    /*
    @brief ��������I�u�W�F�N�g�̃|�W�V������getter
    @return �����_
    */
    Vector3 GetLerpObjectPos() const { return lerpObjectPos; }

    /*
    @brief �Ǐ]����I�u�W�F�N�g�̂Ƃ̊Ԋu���擾
    @return �Ԋu
    */
    Vector3 GetOffsetPosition() const { return offSetPosition; }

    /*
    @brief �Ǐ]����I�u�W�F�N�g�̂Ƃ̊Ԋu���擾
    @return �Ԋu
    */
    bool GetIsChangeMode() const { return isChangeMode; }

    /*
    @brief	��������I�u�W�F�N�g�̃|�W�V�������Z�b�g
    @param ����Ώە��̃|�W�V����
    */
    void SetLerpObjectPos(const Vector3& _pos) { lerpObjectPos = _pos; }

    /*
    @brief	��������I�u�W�F�N�g�̃|�W�V�������Z�b�g
    @param ����Ώە��̃|�W�V����
    */
    void SetOffsetPosition(Vector3 _offset) { offSetPosition = _offset; }

    /*
    @brief	���̃X�e�[�^�X���Z�b�g
    @param _nextState ���̃X�e�[�^�X
    */
    void SetIsChangeMode(bool _isChangeMode) { isChangeMode = _isChangeMode; }

    /*
    @brief	�O���x�N�g�����Z�b�g
    @param _nextForward ���̑O���x�N�g��
    */
    void SetCameraVec(Vector3 _nextForward) { forwardVec = _nextForward; }
};