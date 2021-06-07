#include "StartCountDownSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

StartCountDownSprite::StartCountDownSprite()
	:GameObject(false, PARTICLE)
	, ChangeCount(60)
{
	// 4種のtextureをロード
	firstTexure = RENDERER->GetTexture("Assets/sprite/CountDown3.png");
	secondTexure = RENDERER->GetTexture("Assets/sprite/CountDown2.png");
	thirdTexure = RENDERER->GetTexture("Assets/sprite/CountDown1.png");
	startTexure = RENDERER->GetTexture("Assets/sprite/Start.png");

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

StartCountDownSprite::~StartCountDownSprite()
{
}

void StartCountDownSprite::UpdateGameObject(float _deltaTime)
{
	// 描画フラグがtrueだったら
	if (drawSpriteFlag == true)
	{
		// カウントダウン表示用カウントを数える
		ChackCountProcess();

		// テクスチャの状態をチェック
		ChackTextureProcess();
	}
}

void StartCountDownSprite::ChackCountProcess()
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

void StartCountDownSprite::ChackTextureProcess()
{
	// texture変更フラグがtrueだったら
	if (texChangeFlag == true)
	{
		// 時間ごとのテクスチャに切り替える
		ChangeTextureProcess();
	}
}

void StartCountDownSprite::ChangeTextureProcess()
{
	// time変数を見てそれに応じたtextureをセット
	// 3の時
	if (time == 3)
	{
		sprite->SetTexture(secondTexure);
		texChangeFlag = false;
	}

	// 2の時
	if (time == 2)
	{
		sprite->SetTexture(thirdTexure);
		texChangeFlag = false;
	}

	// 1の時
	if (time == 1)
	{
		sprite->SetTexture(startTexure);
		texChangeFlag = false;
	}

	// 0になったら描画を切ってstateをDeadに
	if (time == 0)
	{
		sprite->SetVisible(false);
		drawSpriteFlag = false;
		CountDownFont::SetCountStartFlag(true);
		state = State::Dead;
	}
}
