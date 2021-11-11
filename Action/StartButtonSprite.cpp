#include "StartButtonSprite.h"
#include "SpriteComponent.h"
#include "Renderer.h"

StartButtonSprite::StartButtonSprite()
	:GameObject(false, Tag::UI)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, -300.0f, 0.0f));
	SetScale(Vector3(0.1f, 0.1f, 0.1f));
	// spriteComponentをnewする
	sprite = new SpriteComponent(this, false);
	// タイトルのtextureをロード
	Texture* tex = RENDERER->GetTexture("Assets/sprite/test_startButton.png");
	// textureをComponentにセット
	sprite->SetTexture(tex);
	// alpha値を初期化
	sprite->SetAlpha(1.0f);
}

StartButtonSprite::~StartButtonSprite()
{
}

void StartButtonSprite::UpdateGameObject(float _deltaTime)
{
}
