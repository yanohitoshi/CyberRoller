#include "StageUnSelectIcon.h"
#include "Renderer.h"
#include "SpriteComponent.h"

StageUnSelectIcon::StageUnSelectIcon(Vector3& _pos, const std::string& _spriteFileName)
	: GameObject(false, Tag::UI)
{
	// ポジションをセット
	SetPosition(Vector3(300.0f, -300.0f, 0.0f));
	SetScale(Vector3(0.2f, 0.2f, 0.2f));
	SetPosition(_pos);
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

StageUnSelectIcon::~StageUnSelectIcon()
{
}

void StageUnSelectIcon::UpdateGameObject(float _deltaTime)
{
}
