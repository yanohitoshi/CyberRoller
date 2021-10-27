#pragma once
#include "GameObject.h"

class SpriteComponent;
class Texture;
enum class CollectionTag;

class UnCollectedSprite :
    public GameObject
{
public:

    /*
    @brief	�R���X�g���N�^
    */
    UnCollectedSprite(CollectionTag collectionTag);

    /*
    @fn �f�X�g���N�^
    @brief  object�̍폜���s��
    */
    ~UnCollectedSprite()override;

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

public:
    
    /*
    @brief	SpriteComponent��getter
    @return	SpriteComponent�̃|�C���^
    */
    SpriteComponent* GetSpriteComponent() { return sprite; }

};

