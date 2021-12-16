//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CollectedEffectSprite.h"
#include "SpriteComponent.h"
#include "CollectionObject.h"
#include "GraphicsResourceManager.h"

/*
@brief	コンストラクタ
@param 何番目の収集物かのタグ
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
	tex = GRAPHICS_RESOURCE->CreateTexture("Assets/sprite/collection/AuroraRing.png");
	sprite->SetTexture(tex);
	alpha = 1.0f;
	sprite->SetAlpha(alpha);
	sprite->SetVisible(false);
	scale = 0.0f;
	sprite->SetScale(scale);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
CollectedEffectSprite::~CollectedEffectSprite()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void CollectedEffectSprite::UpdateGameObject(float _deltaTime)
{
	// 描画する状態だったら
	if (sprite->GetVisible())
	{
		// scaleとalpha値を更新
		scale += AddScale;
		sprite->SetScale(scale);
		alpha -= SubAlpha;
		sprite->SetAlpha(alpha);
	}

	// alpha値が0.0以下になったら
	if (alpha < 0.0f)
	{
		// 描画を切る
		sprite->SetVisible(false);
	}
}

/*
@fn 初期化関数
*/
void CollectedEffectSprite::Reset()
{
	alpha = 1.0f;
	sprite->SetAlpha(alpha);
	scale = 0.0f;
	sprite->SetScale(scale);
}
