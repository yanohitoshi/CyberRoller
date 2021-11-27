#include "StartButtonSprite.h"
#include "SpriteComponent.h"
#include "RenderingObjectManager.h"

StartButtonSprite::StartButtonSprite()
	:GameObject(false, Tag::UI)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, -300.0f, 0.0f));
	SetScale(Vector3(0.1f, 0.1f, 0.1f));
	// spriteComponentをnewする
	sprite = new SpriteComponent(this, false);
	// タイトルのtextureをロード
	Texture* tex = RENDERING_OBJECT_MANAGER->CreateTexture("Assets/sprite/title/startButton.png");
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
