#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class CollectionObject;
class CollectedSprite;
class UnCollectedSprite;
class CollectedEffectSprite;

/*
@file CollectionUI.h
@brief ���W���pUI���Ǘ�����N���X
*/
class CollectionUI :
    public GameObject
{
public:
    
    /*
    @brief	�R���X�g���N�^
    */
    CollectionUI(CollectionObject* _owner);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~CollectionUI()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

    /*
    @fn �ʏ펞�̕`��
    */
    void DrawInGame();

    /*
    @fn �`������Z�b�g����
    */
    void ResetDraw();

    /*
    @fn �`�悷��|�W�V������ύX����
    @param _position �Z�b�g����ʒu
    */
    void SetDrawPosition(Vector3 _position);

private:

    // �I�[�i�[�ƂȂ���W���̃|�C���^�ϐ�
    CollectionObject* owner;

    // ���ꂼ���sprite�̃|�C���^�ϐ�
    CollectedSprite* collectedSprite;
    UnCollectedSprite* unCollectedSprite;
    CollectedEffectSprite* collectedEffectSprite;

    // �Q�[�������ǂ���
    bool isInGame;
};

