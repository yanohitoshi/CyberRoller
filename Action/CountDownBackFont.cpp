//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CountDownBackFont.h"
#include "GraphicsResourceManager.h"
#include "Font.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

/*
@brief	コンストラクタ
@param	カウントする時間
*/
CountDownBackFont::CountDownBackFont(int _time)
	: GameObject(false, Tag::UI)
	, AddTimeCount(60)
{
	// ポジションをセット
	SetPosition(Vector3(695.0f, 480.0f, 0.0f));
	//  SpriteComponent初期化
	sprite = new SpriteComponent(this,false ,105);
	sprite->SetAlpha(1.0f);
	// メンバー変数初期化
	time = _time;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
CountDownBackFont::~CountDownBackFont()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void CountDownBackFont::UpdateGameObject(float _deltaTime)
{
	// ゲームスタートしたらカウント開始
	if (CountDownFont::GetCountStartFlag() == true)
	{
		// フレームカウントを数える
		frameCount++;
		// 60になったら
		if (frameCount >= AddTimeCount)
		{
			// timeを減らす
			time -= 1;
			frameCount = 0;
		}
	}

	// 1以上の時は黒色で描画
	if (time >= 1)
	{
		sprite->SetTexture(GRAPHICS_RESOURCE->GetTimeBlackTexture(time - 1));
	}
	// textureを先に作ってvector配列に格納している都合上0を描画するときnullにアクセスしてしまうのを回避
	if (time == 0)
	{
		sprite->SetTexture(GRAPHICS_RESOURCE->GetTimeBlackTexture(-1));
	}

	// timeが-1以下になったらタイムオーバーにする
	if (time <= -1)
	{
		sprite->SetVisible(false);
	}
}