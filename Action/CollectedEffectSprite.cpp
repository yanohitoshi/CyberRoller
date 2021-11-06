#include "CollectedEffectSprite.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "CollectionObject.h"

CollectedEffectSprite::CollectedEffectSprite(CollectionTag collectionTag)
	: GameObject(false, Tag::UI)
{
	switch (collectionTag)
	{
	case CollectionTag::FIRST:
		// ポジションをセット
		SetPosition(Vector3(-850.0f, 480.0f, 0.0f));
		break;
	case CollectionTag::SECOND:
		// ポジションをセット
		SetPosition(Vector3(-700.0f, 480.0f, 0.0f));
		break;
	case CollectionTag::THIRD:
		// ポジションをセット
		SetPosition(Vector3(-550.0f, 480.0f, 0.0f));
		break;
	}

	// SpriteComponent初期化
	sprite = new SpriteComponent(this, false);
	tex = RENDERER->GetTexture("Assets/sprite/AuroraRing.png");
	sprite->SetTexture(tex);
	alpha = 1.0f;
	sprite->SetAlpha(alpha);
	sprite->SetVisible(false);
	scale = 0.0f;
	sprite->SetScale(scale);
}

CollectedEffectSprite::~CollectedEffectSprite()
{
}

void CollectedEffectSprite::UpdateGameObject(float _deltaTime)
{
	if (sprite->GetVisible())
	{
		scale += 0.1;
		sprite->SetScale(scale);
		alpha -= 0.05;
		sprite->SetAlpha(alpha);
	}

	if (alpha < 0.0f)
	{
		sprite->SetVisible(false);
	}
}

void CollectedEffectSprite::Reset()
{
	alpha = 1.0f;
	sprite->SetAlpha(alpha);
	scale = 0.0f;
	sprite->SetScale(scale);
}
