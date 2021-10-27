#include "CollectionUI.h"
#include "CollectedSprite.h"
#include "UnCollectedSprite.h"
#include "SpriteComponent.h"
#include "CollectionObject.h"
#include "CollectedEffectSprite.h"

CollectionUI::CollectionUI(CollectionObject* _owner)
	: GameObject(false, Tag::UI)
{
	owner = _owner;
	CollectionTag tag = owner->GetCollectionTag();
	collectedSprite = new CollectedSprite(tag);
	unCollectedSprite = new UnCollectedSprite(tag);
	collectedEffectSprite = new CollectedEffectSprite(tag);
}

CollectionUI::~CollectionUI()
{
}

void CollectionUI::UpdateGameObject(float _deltaTime)
{
	if (owner->GetIsCollected())
	{
		collectedSprite->GetSpriteComponent()->SetVisible(true);
		collectedEffectSprite->GetSpriteComponent()->SetVisible(true);
		unCollectedSprite->GetSpriteComponent()->SetVisible(false);
	}
	else
	{
		collectedSprite->GetSpriteComponent()->SetVisible(false);
		collectedEffectSprite->GetSpriteComponent()->SetVisible(false);
		unCollectedSprite->GetSpriteComponent()->SetVisible(true);
	}
}
