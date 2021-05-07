#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CameraObjectBase.h"

/*
@file TitleCamre.h
@brief �^�C�g����ʂ��f���J�����̐����ƍX�V����
       CameraObjectBase���p��
*/
class TitleCameraObject :
    public CameraObjectBase
{
public:

    /*
    @brief	�R���X�g���N�^
    @param	�|�W�V����
    */
    TitleCameraObject(const Vector3 _pos);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~TitleCameraObject();

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	deltaTime�Œ�
    */
    void UpdateGameObject(float _deltaTime = 1.0f);
    
    /*
    @fn ���͂������Ŏ󂯎��X�V�֐�
    @brief ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
    */
    void GameObjectInput(const InputState& _keyState);

private:

    // �^�C�g���p�v���C���[�̃|�W�V�����𗘗p���Đ�������̂ňʒu�����炷���߂̒萔
    const float ShiftPosition;

    // ������𒍎�����悤�ɂ������̂�Z�������炷�萔
    const float ShiftGazePoint;

    // ����ꏊ�̃^�[�Q�b�gVector3
    Vector3 target;

    // view�s��
    Matrix4 view;

};

