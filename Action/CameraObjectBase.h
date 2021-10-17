#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

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
    @brief	player�ȊO�̂��̂𒍎�����ۂɎg��setter
    @param ����Ώە��̃|�W�V����
    */
    void SetLerpObjectPos(const Vector3& _pos) { lerpObjectPos = _pos; }

    /*
    @brief ���X�|�[�������Ƃ��ɃJ�����̈ʒu��������ԂɃZ�b�g����֐�
    */
    void ResetCamera() { yaw = Math::ToRadians(180); pitch = Math::ToRadians(30); }

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
    //�J������]�v�Z�p�̃��[�ƃs�b�`
    float yaw;
    float pitch;
private:

public:
    
    /*
    @brief �J�����̑O���x�N�g���𓾂邽�߂�getter
    @param �J�����̑O���x�N�g��
    */
    Vector3 GetCameraVec() { return forwardVec; }

};

