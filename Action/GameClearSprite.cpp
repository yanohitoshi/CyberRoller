#include "GameClearSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "PlayerObject.h"

GameClearSprite::GameClearSprite(PlayerObject* _playerObject)
	:GameObject(false, Tag::UI)
	, DRAW_COUNT(120)
{

	playerObject = _playerObject;

	// ポジションをセット
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// textureをロード
	Texture* tex = RENDERER->GetTexture("Assets/sprite/gameclear2.png");
	// SpriteComponent初期化
	sprite = new SpriteComponent(this,false);
	sprite->SetTexture(tex);
	sprite->SetVisible(false);
	sprite->SetAlpha(1.0f);
	// メンバー変数初期化
	frameCount = 0;
}

GameClearSprite::~GameClearSprite()
{
}

void GameClearSprite::UpdateGameObject(float _deltaTime)
{
	// クリア状態になったら
	if (playerObject->GetClearFlag() == true)
	{
		// フレームカウントを数える
		++frameCount;
		// 120カウント超えたら描画する
		if (frameCount >= DRAW_COUNT)
		{
			sprite->SetVisible(true);
		}
	}
}
