#include "StageSelectIconSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"

StageSelectIconSprite::StageSelectIconSprite(Vector3& _pos, const std::string& _spriteFileName)
	: GameObject(false, Tag::UI)
{
	// ポジションをセット
	SetPosition(Vector3(0.0f, -300.0f, 0.0f));
	SetPosition(_pos);
	SetScale(Vector3(0.25f, 0.25f, 0.25f));
	// spriteComponenをnewする
	sprite = new SpriteComponent(this, false);
	// 背景テクスチャをロード
	Texture* tex = RENDERER->GetTexture(_spriteFileName);
	// 背景テクスチャをセット
	sprite->SetTexture(tex);
	// 映す映さないをセット
	sprite->SetVisible(true);
	// alpha値をセット
	sprite->SetAlpha(1.0f);
}

StageSelectIconSprite::~StageSelectIconSprite()
{
}

void StageSelectIconSprite::UpdateGameObject(float _deltaTime)
{
}
