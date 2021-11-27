//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "StartCountDownSprite.h"
#include "RenderingObjectManager.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

/*
@brief	コンストラクタ
*/
StartCountDownSprite::StartCountDownSprite()
	:GameObject(false, PARTICLE)
	, ChangeCount(60)
{
	// 4種のtextureをロード
	firstTexure = RENDERING_OBJECT_MANAGER->GetTexture("Assets/sprite/information/Three.png");
	secondTexure = RENDERING_OBJECT_MANAGER->GetTexture("Assets/sprite/information/Two.png");
	thirdTexure = RENDERING_OBJECT_MANAGER->GetTexture("Assets/sprite/information/One.png");
	startTexure = RENDERING_OBJECT_MANAGER->GetTexture("Assets/sprite/information/Start.png");

	// SpriteComponentを初期化
	sprite = new SpriteComponent(this, false);
	sprite->SetTexture(firstTexure);
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	sprite->SetVisible(false);
	sprite->SetAlpha(1.0f);
	// メンバー変数初期化
	timeStartCount = 0;
	time = 4;
	texChangeFlag = false;
	drawSpriteFlag = true;
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
StartCountDownSprite::~StartCountDownSprite()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void StartCountDownSprite::UpdateGameObject(float _deltaTime)
{
	// 描画フラグがtrueだったら
	if (drawSpriteFlag == true)
	{
		// カウントダウン表示用カウントを数える
		CheckCountProcess();

		// テクスチャの状態をチェック
		CheckTextureProcess();
	}
}

/*
@fn カウントダウン表示時間カウントを数える関数
*/
void StartCountDownSprite::CheckCountProcess()
{
	// カウント計測
	++timeStartCount;
	// カウントが60以下だったら
	if (timeStartCount >= ChangeCount)
	{
		// 描画する
		sprite->SetVisible(true);
		// フレームカウントを取る
		frameCount++;
		// 60フレーム後ごとにtextureを切り替える
		if (frameCount >= ChangeCount)
		{
			time -= 1;
			frameCount = 0;
			// texture変更フラグをtrueに
			texChangeFlag = true;
		}
	}
}

/*
@fn テクスチャの状態を見る関数
*/
void StartCountDownSprite::CheckTextureProcess()
{
	// texture変更フラグがtrueだったら
	if (texChangeFlag == true)
	{
		// 時間ごとのテクスチャに切り替える
		ChangeTextureProcess();
	}
}

/*
@fn テクスチャを切り替える関数
*/
void StartCountDownSprite::ChangeTextureProcess()
{
	// time変数を見てそれに応じたtextureをセット
	switch (time)
	{
	case TimeNum::TREE:
		sprite->SetTexture(secondTexure);
		texChangeFlag = false;
		break;
	case TimeNum::TOW:
		sprite->SetTexture(thirdTexure);
		texChangeFlag = false;
		break;
	case TimeNum::ONE:
		sprite->SetTexture(startTexure);
		// スタートtextureになった時のみ拡大
		SetScale(2.0f);
		texChangeFlag = false;
		break;
	case TimeNum::ZERO:
		sprite->SetVisible(false);
		drawSpriteFlag = false;
		CountDownFont::SetCountStartFlag(true);
		state = State::Dead;
		break;
	}
}