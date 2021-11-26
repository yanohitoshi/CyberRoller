#pragma once
#include "GameObject.h"

class SpriteComponent;
class StageSelectSceneUI;

class StageSelectIconSprite :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    */
    StageSelectIconSprite(StageSelectSceneUI* _owner, SceneState _state, const std::string& _spriteFileName);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~StageSelectIconSprite();

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �w�i�p�X�v���C�gComponent
    SpriteComponent* sprite;
    SceneState myState;
    // �`�悷�邩�ǂ���
    bool isVisible;

    // �e�X�e�[�W�A�C�R���̃|�W�V����
    const Vector3 FirstStagePosition;
    const Vector3 SecondStagePosition;
    const Vector3 ThirdStagePosition;
    const Vector3 FourthStagePosition;
    const Vector3 FinalStagePosition;

public:

    /*
    @brief	�`�悷�邩�ǂ������Z�b�g
    @param	_isVisible �`�悷�邩�ǂ���
    */
    void SetIsVisible(bool _isVisible) { isVisible = _isVisible; }

};

