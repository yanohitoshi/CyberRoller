//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TimeSprite.h"
#include "RenderingObjectManager.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

/*
@brief	コンストラクタ
*/
TimeSprite::TimeSprite()
	: GameObject(false, Tag::UI)
{
	// ポジションをセット
	SetPosition(Vector3(700.0f, 480.0f, 0.0f));
	// SpriteComponent初期化
	sprite = new SpriteComponent(this, false);
	tex = RENDERING_OBJECT_MANAGER->CreateTexture("Assets/sprite/time/Time_UI.png");
	sprite->SetTexture(tex);
	sprite->SetAlpha(1.0f);
	// メンバー変数初期化
	frameCount = 0;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
TimeSprite::~TimeSprite()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void TimeSprite::UpdateGameObject(float _deltaTime)
{
	// タイムオーバーになったら描画を切る
	if (CountDownFont::GetTimeOverFlag() == true)
	{
		sprite->SetVisible(false);
	}
}