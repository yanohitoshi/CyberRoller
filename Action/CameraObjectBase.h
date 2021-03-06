#pragma once
#include "GameObject.h"

//GameObject���p�������J�����̊��N���X
class CameraObjectBase :
    public GameObject
{

public:

    /*
    @brief	�R���X�g���N�^
    @param	�ė��p���邩�t���O
    @param	ObjectTag
    */
    CameraObjectBase(bool _reUseGameObject, const Tag _objectTag);
    ~CameraObjectBase();

    /*
    @brief	�X�V����
    @param	�Ō�̃t���[������������̂ɗv��������
    */
    virtual void UpdateGameObject(float _deltaTime = 1.0f);
    virtual void GameObjectInput(const InputState& _keyState);

private:

};

