#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

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

    //�ړ���position
    Vector3 tmpMovePos;
    Vector3 tmpPosition;
    //�Ǐ]��̃I�u�W�F�N�g���W
    Vector3 lerpObjectPos;
    // view�s��
    Matrix4 view;
    // �v���C���[�̃|�C���^��ێ����邽�߂̕ϐ�
    PlayerObject* playerObject;
    // ���`�ۊǎ��Ƀf���^�^�C����������Ƃ��p�̕␳�萔
    const float DeltaCorrection;
    //�J������]�v�Z�p�̃��[�ƃs�b�`
    float yaw;
    float pitch;

    Vector3 offSetPosition;

    // ����enemy��state��Ԃ�ۑ����邽�߂̕ϐ�
    CameraState nowState;
    // �ύX���ꂽ����enemy��state��Ԃ�ۑ����邽�߂̕ϐ�
    CameraState nextState;
    // �Sstate���i�[�����}�b�v
    std::unordered_map<CameraState, CameraObjectStateBase*> statePoolMap;

private:


public:
    
    /*
    @brief �J�����̑O���x�N�g���𓾂邽�߂�getter
    @return �J�����̑O���x�N�g��
    */
    Vector3 GetCameraVec() { return forwardVec; }

    /*
    @brief �Ǐ]����I�u�W�F�N�g�̃|�C���^�𓾂邽�߂�getter
    @return �Ǐ]����I�u�W�F�N�g�̃|�C���^
    */
    PlayerObject* GetLerpObject() { return playerObject; }

    /*
    @brief player�ȊO�̂��̂𒍎�����ꍇ�̃|�W�V�������邽�߂�getter
    @return �����_
    */
    Vector3 GetLerpObjectPos() { return lerpObjectPos; }

    /*
    @brief	player�ȊO�̂��̂𒍎�����ۂɎg��setter
    @param ����Ώە��̃|�W�V����
    */
    void SetLerpObjectPos(const Vector3& _pos) { lerpObjectPos = _pos; }

    Vector3 GetOffsetPosition() { return offSetPosition; }

    void SetOffsetPosition(Vector3 _offset) { offSetPosition = _offset; }

    void SetNextState(CameraState _nextState) { nextState = _nextState; }
    void SetCameraVec(Vector3 _nextForward) { forwardVec = _nextForward; }
};

