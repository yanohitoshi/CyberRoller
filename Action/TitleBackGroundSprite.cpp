//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TitleBackGroundSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"

/*
@fn コンストラクタ
*/
TitleBackGroundSprite::TitleBackGroundSprite()
	:GameObject(false, Tag::UI)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// spriteComponenをnewする
	sprite = new SpriteComponent(this, true);
	// 背景テクスチャをロード
	Texture* tex = RENDERER->GetTexture("Assets/sprite/BackGround_SP/TitleBackGround_1.png");
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
TitleBackGroundSprite::~TitleBackGroundSprite()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void TitleBackGroundSprite::UpdateGameObject(float _deltaTime)
{
}