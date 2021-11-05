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
	isInGame = true;
}

CollectionUI::~CollectionUI()
{
}

void CollectionUI::UpdateGameObject(float _deltaTime)
{
}

void CollectionUI::DrawInGame()
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

void CollectionUI::ResetDraw()
{
	collectedSprite->GetSpriteComponent()->SetVisible(false);
	collectedEffectSprite->GetSpriteComponent()->SetVisible(false);
	collectedEffectSprite->Reset();
	unCollectedSprite->GetSpriteComponent()->SetVisible(false);
}

void CollectionUI::SetDrawPosition(Vector3 _position)
{
	collectedSprite->SetPosition(_position);
	unCollectedSprite->SetPosition(_position);
	collectedEffectSprite->SetPosition(_position);
}
