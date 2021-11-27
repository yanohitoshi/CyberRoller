//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TitleSprite.h"
#include "RenderingObjectManager.h"
#include "SpriteComponent.h"

/*
@fn コンストラクタ
*/
TitleSprite::TitleSprite()
	:GameObject(false, Tag::UI)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, 300.0f, 0.0f));
	SetScale(Vector3(0.2f, 0.2f, 0.2f));
	// spriteComponenをnewする
	sprite = new SpriteComponent(this, false);
	// 背景テクスチャをロード
	Texture* tex = RENDERING_OBJECT_MANAGER->GetTexture("Assets/sprite/title/Title.png");
	// 背景テクスチャをセット
	sprite->SetTexture(tex);
	// 映す映さないをセット
	sprite->SetVisible(true);
	// alpha値をセット
	sprite->SetAlpha(1.0f);

}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
TitleSprite::~TitleSprite()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void TitleSprite::UpdateGameObject(float _deltaTime)
{
}