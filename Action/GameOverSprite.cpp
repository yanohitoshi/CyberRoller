//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameOverSprite.h"
#include "SpriteComponent.h"
#include "ContinueSprite.h"
#include "GraphicsResourceManager.h"

/*
@brief	コンストラクタ
*/
GameOverSprite::GameOverSprite()
	:GameObject(false, Tag::UI)
	, DrawCount(60)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// textureをロード
	Texture* tex = GRAPHICS_RESOURCE->CreateTexture("Assets/sprite/information/gameover.png");
	// SpriteComponent初期化
	sprite = new SpriteComponent(this,false);
	sprite->SetTexture(tex);
	sprite->SetVisible(false);
	sprite->SetAlpha(1.0f);
	// メンバー変数初期化
	frameCount = 0;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
GameOverSprite::~GameOverSprite()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void GameOverSprite::UpdateGameObject(float _deltaTime)
{
	// コンテニュー選択状態の時コンテニューが選択されなかったら
	if (ContinueSprite::GetDrawFlag() == false && ContinueSprite::GetContinueFlag() == false)
	{
		// フレームカウントを数える
		++frameCount;
		// カウントが60になったら描画する
		if (frameCount >= DrawCount)
		{
			sprite->SetVisible(true);
		}
	}
}