#include "UnCollectedSprite.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "CollectionObject.h"

UnCollectedSprite::UnCollectedSprite(CollectionTag collectionTag)
	: GameObject(false, Tag::UI)
{
	switch (collectionTag)
	{
	case CollectionTag::FIRST:
		// �|�W�V�������Z�b�g
		SetPosition(Vector3(-850.0f, 480.0f, 0.0f));
		break;
	case CollectionTag::SECOND:
		// �|�W�V�������Z�b�g
		SetPosition(Vector3(-700.0f, 480.0f, 0.0f));
		break;
	case CollectionTag::THIRD:
		// �|�W�V�������Z�b�g
		SetPosition(Vector3(-550.0f, 480.0f, 0.0f));
		break;
	}

	// SpriteComponent������
	sprite = new SpriteComponent(this, false);
	tex = RENDERER->GetTexture("Assets/sprite/collection/UnCollected.png");
	sprite->SetTexture(tex);
	sprite->SetAlpha(1.0f);
}

UnCollectedSprite::~UnCollectedSprite()
{
}

void UnCollectedSprite::UpdateGameObject(float _deltaTime)
{
}
