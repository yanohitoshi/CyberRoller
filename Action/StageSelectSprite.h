#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class SpriteComponent;
class StageSelectSceneUI;

/*
@file StageSelectSprite.h
@brief �I������Ă���stage�摜��\������
*/
class StageSelectSprite :
    public GameObject
{
public:

    /*
    @fn �R���X�g���N�^
    @parma �e�N���X�̃|�C���^
    @parma �V�[���̃X�e�[�^�X
    @parma �`�悷��摜�̃t�@�C���l�[��
    */
    StageSelectSprite(StageSelectSceneUI* _owner,SceneState _state,const std::string& _spriteFileName);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~StageSelectSprite();

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �w�i�p�X�v���C�gComponent
    SpriteComponent* sprite;
    // �����̃V�[���X�e�[�^�X
    SceneState myState;

    // �`����s�����ۂ�
    bool isVisible;

public:

    /*
    @fn �`����s�����ۂ����Z�b�g����
    @param _isVisible�@�`�悷�邩�ǂ���
    */
    void SetIsVisible(bool _isVisible) { isVisible = _isVisible; }
};