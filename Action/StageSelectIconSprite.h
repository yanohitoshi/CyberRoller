#pragma once
#include "GameObject.h"

class SpriteComponent;

class StageSelectIconSprite :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    */
    StageSelectIconSprite(Vector3& _pos, const std::string& _spriteFileName);

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
};

