#include "CollectedSprite.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "CollectionObject.h"

CollectedSprite::CollectedSprite(CollectionTag collectionTag)
	: GameObject(false, Tag::UI)
	, FirstCollectionPosition(Vector3(-850.0f, 480.0f, 0.0f))
	, SecondCollectionPosition(Vector3(-700.0f, 480.0f, 0.0f))
	, ThirdCollectionPosition(Vector3(-550.0f, 480.0f, 0.0f))
{
	switch (collectionTag)
	{
	case CollectionTag::FIRST:
		// ポジションをセット
		SetPosition(FirstCollectionPosition);
		break;
	case CollectionTag::SECOND:
		// ポジションをセット
		SetPosition(SecondCollectionPosition);
		break;
	case CollectionTag::THIRD:
		// ポジションをセット
		SetPosition(ThirdCollectionPosition);
		break;
	}

	// SpriteComponent初期化
	sprite = new SpriteComponent(this, false);
	tex = RENDERER->GetTexture("Assets/sprite/collection/Collected.png");
	sprite->SetTexture(tex);
	sprite->SetAlpha(1.0f);
}

CollectedSprite::~CollectedSprite()
{
}

void CollectedSprite::UpdateGameObject(float _deltaTime)
{
}
