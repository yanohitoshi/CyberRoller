#pragma once
#include "CameraObjectBase.h"

/*
@file ResultCameraObject.h
@brief ���U���g�V�[���ł̃J����class
*/
class ResultCameraObject :
    public CameraObjectBase
{
public:

    /*
    @brief	�R���X�g���N�^
    @param	�J�����̒����_
    */
    ResultCameraObject(const Vector3 _pos);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~ResultCameraObject();

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	deltaTime�Œ�
    */
    void UpdateGameObject(float _deltaTime = 1.0f);

private:

    // �J�����̒����_�𗘗p���Đ�������̂ňʒu�����炷���߂̒萔
    const float ShiftPosition;

    // ����ꏊ�̃^�[�Q�b�gVector3
    Vector3 target;

    // view�s��
    Matrix4 view;
};

