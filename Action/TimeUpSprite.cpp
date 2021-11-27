//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TimeUpSprite.h"
#include "RenderingObjectManager.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

// staticメンバーを初期化
bool TimeUpSprite::drawFlag = true;

/*
@fn コンストラクタ
*/
TimeUpSprite::TimeUpSprite()
	:GameObject(false, Tag::UI)
	, DrawCount(120)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// SpriteComponent初期化
	sprite = new SpriteComponent(this, false);
	Texture* tex = RENDERING_OBJECT_MANAGER->GetTexture("Assets/sprite/information/timeup.png");
	sprite->SetTexture(tex);
	sprite->SetVisible(false);
	sprite->SetAlpha(1.0f);
	// メンバー変数初期化
	frameCount = 0;
	visibleFlag = true;

}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
TimeUpSprite::~TimeUpSprite()
{
	// 静的変数初期化
	drawFlag = true;
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void TimeUpSprite::UpdateGameObject(float _deltaTime)
{
	// タイムオーバーかつ1度だけ描画フラグがtrueだったら
	if (CountDownFont::GetTimeOverFlag() == true && visibleFlag == true)
	{
		// フレームカウント計測
		++frameCount;
		// 描画する
		sprite->SetVisible(true);
		// フレームカウントが120を超えたら
		if (frameCount >= DrawCount)
		{
			//　1度だけ描画フラグをfalseに
			visibleFlag = false;
			// 描画を切る
			sprite->SetVisible(false);
			// 描画されているかフラグをfalseに
			drawFlag = false;
		}
	}
}