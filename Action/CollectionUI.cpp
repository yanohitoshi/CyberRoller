#include "CollectionUI.h"
#include "CollectedSprite.h"
#include "UnCollectedSprite.h"
#include "SpriteComponent.h"
#include "CollectionObject.h"

CollectionUI::CollectionUI(CollectionObject* _owner)
	: GameObject(false, Tag::UI)
{
	owner = _owner;
	CollectionTag tag = owner->GetCollectionTag();
	collectedSprite = new CollectedSprite(tag);
	unCollectedSprite = new UnCollectedSprite(tag);
}

CollectionUI::~CollectionUI()
{
}

void CollectionUI::UpdateGameObject(float _deltaTime)
{
	if (owner->GetIsCollected())
	{
		collectedSprite->GetSpriteComponent()->SetVisible(true);
		unCollectedSprite->GetSpriteComponent()->SetVisible(false);
	}
	else
	{
		collectedSprite->GetSpriteComponent()->SetVisible(false);
		unCollectedSprite->GetSpriteComponent()->SetVisible(true);
	}
}
