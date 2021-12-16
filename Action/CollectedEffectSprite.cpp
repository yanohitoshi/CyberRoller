//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CollectedEffectSprite.h"
#include "SpriteComponent.h"
#include "CollectionObject.h"
#include "GraphicsResourceManager.h"

/*
@brief	�R���X�g���N�^
@param ���Ԗڂ̎��W�����̃^�O
*/
CollectedEffectSprite::CollectedEffectSprite(CollectionTag collectionTag)
	: GameObject(false, Tag::UI)
	, FirstCollectionPosition(Vector3(-850.0f, 480.0f, 0.0f))
	, SecondCollectionPosition(Vector3(-700.0f, 480.0f, 0.0f))
	, ThirdCollectionPosition(Vector3(-550.0f, 480.0f, 0.0f))
	, AddScale(0.1f)
	, SubAlpha(0.05f)
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
	tex = GRAPHICS_RESOURCE->CreateTexture("Assets/sprite/collection/AuroraRing.png");
	sprite->SetTexture(tex);
	alpha = 1.0f;
	sprite->SetAlpha(alpha);
	sprite->SetVisible(false);
	scale = 0.0f;
	sprite->SetScale(scale);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
CollectedEffectSprite::~CollectedEffectSprite()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void CollectedEffectSprite::UpdateGameObject(float _deltaTime)
{
	// �`�悷���Ԃ�������
	if (sprite->GetVisible())
	{
		// scale��alpha�l���X�V
		scale += AddScale;
		sprite->SetScale(scale);
		alpha -= SubAlpha;
		sprite->SetAlpha(alpha);
	}

	// alpha�l��0.0�ȉ��ɂȂ�����
	if (alpha < 0.0f)
	{
		// �`���؂�
		sprite->SetVisible(false);
	}
}

/*
@fn �������֐�
*/
void CollectedEffectSprite::Reset()
{
	alpha = 1.0f;
	sprite->SetAlpha(alpha);
	scale = 0.0f;
	sprite->SetScale(scale);
}
