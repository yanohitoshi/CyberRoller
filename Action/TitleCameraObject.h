#pragma once
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
    ~TitleCameraObject();

    /*
    @brief	�X�V����
    @param	deltaTime�Œ�
    */
    void UpdateGameObject(float _deltaTime = 1.0f);
    void GameObjectInput(const InputState& _keyState);

private:

    Vector3 target;
    Matrix4 view;

};

