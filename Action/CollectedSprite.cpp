//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CollectedSprite.h"
#include "SpriteComponent.h"
#include "CollectionObject.h"
#include "GraphicsResourceManager.h"
/*
@brief	�R���X�g���N�^
@param ���Ԗڂ̎��W�����̃^�O
*/
CollectedSprite::CollectedSprite(CollectionTag collectionTag)
	: GameObject(false, Tag::UI)
	, FirstCollectionPosition(Vector3(-850.0f, 480.0f, 0.0f))
	, SecondCollectionPosition(Vector3(-700.0f, 480.0f, 0.0f))
	, ThirdCollectionPosition(Vector3(-550.0f, 480.0f, 0.0f))
{
	switch (collectionTag)
	{
	case CollectionTag::FIRST:
		// �|�W�V�������Z�b�g
		SetPosition(FirstCollectionPosition);
		break;
	case CollectionTag::SECOND:
		// �|�W�V�������Z�b�g
		SetPosition(SecondCollectionPosition);
		break;
	case CollectionTag::THIRD:
		// �|�W�V�������Z�b�g
		SetPosition(ThirdCollectionPosition);
		break;
	}

	// SpriteComponent������
	sprite = new SpriteComponent(this, false);
	tex = GRAPHICS_RESOURCE->CreateTexture("Assets/sprite/collection/Collected.png");
	sprite->SetTexture(tex);
	sprite->SetAlpha(1.0f);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
CollectedSprite::~CollectedSprite()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void CollectedSprite::UpdateGameObject(float _deltaTime)
{
}
