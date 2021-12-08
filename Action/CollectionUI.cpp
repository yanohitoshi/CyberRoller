//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CollectionUI.h"
#include "CollectedSprite.h"
#include "UnCollectedSprite.h"
#include "SpriteComponent.h"
#include "CollectionObject.h"
#include "CollectedEffectSprite.h"

/*
@brief	コンストラクタ
@param 親クラスのポインタ
*/
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

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
CollectionUI::~CollectionUI()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void CollectionUI::UpdateGameObject(float _deltaTime)
{
}

/*
@fn 通常時の描画
*/
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

/*
@fn 描画をリセットする
*/
void CollectionUI::ResetDraw()
{
	collectedSprite->GetSpriteComponent()->SetVisible(false);
	collectedEffectSprite->GetSpriteComponent()->SetVisible(false);
	collectedEffectSprite->Reset();
	unCollectedSprite->GetSpriteComponent()->SetVisible(false);
}

/*
@fn 描画するポジションを変更する
@param _position セットする位置
*/
void CollectionUI::SetDrawPosition(Vector3 _position)
{
	collectedSprite->SetPosition(_position);
	unCollectedSprite->SetPosition(_position);
	collectedEffectSprite->SetPosition(_position);
}
