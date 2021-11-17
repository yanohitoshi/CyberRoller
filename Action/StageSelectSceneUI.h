#pragma once
#include "GameObject.h"

// �N���X�̑O���錾
class SkyBoxObject;

class StageSelectSceneUI :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @brief  object�̐������s��
    */
    StageSelectSceneUI();

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~StageSelectSceneUI()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �X�J�C�{�b�N�X�N���X�̃|�C���^
    SkyBoxObject* skyBox;
};

