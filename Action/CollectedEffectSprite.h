#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class SpriteComponent;
class Texture;
enum class CollectionTag;

/*
@file CollectedEffectSprite.h
@brief ���W�����l�������Ƃ��̃G�t�F�N�g��\������
*/
class CollectedEffectSprite :
    public GameObject
{
public:

    /*
    @brief	�R���X�g���N�^
    @param ���Ԗڂ̎��W�����̃^�O
    */
    CollectedEffectSprite(CollectionTag collectionTag);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~CollectedEffectSprite()override;

    /*
    @fn �A�b�v�f�[�g�֐�
    @brief	�X�V�������s��
    @param	_deltaTime �O�̃t���[���ł�����������
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // �X�v���C�gComponent
    SpriteComponent* sprite;
    // texture
    Texture* tex;
    // �t���[���J�E���g�ϐ�
    int frameCount;
    // �g��k���l
    float scale;
    // �A���t�@�l
    float alpha;

    // �e���W��UI�̃|�W�V����
    const Vector3 FirstCollectionPosition;
    const Vector3 SecondCollectionPosition;
    const Vector3 ThirdCollectionPosition;

    // �ǉ�����g��l
    const float AddScale;
    // ���炷alpha�l
    const float SubAlpha;

public:

    /*
    @brief	SpriteComponent��getter
    @return	SpriteComponent�̃|�C���^
    */
    SpriteComponent* GetSpriteComponent() { return sprite; }

    /*
    @fn �������֐�
    */
    void Reset();
};

