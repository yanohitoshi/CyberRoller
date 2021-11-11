#include "StartButtonSprite.h"
#include "SpriteComponent.h"
#include "Renderer.h"

StartButtonSprite::StartButtonSprite()
	:GameObject(false, Tag::UI)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, -300.0f, 0.0f));
	SetScale(Vector3(0.1f, 0.1f, 0.1f));
	// spriteComponent��new����
	sprite = new SpriteComponent(this, false);
	// �^�C�g����texture�����[�h
	Texture* tex = RENDERER->GetTexture("Assets/sprite/test_startButton.png");
	// texture��Component�ɃZ�b�g
	sprite->SetTexture(tex);
	// alpha�l��������
	sprite->SetAlpha(1.0f);
}

StartButtonSprite::~StartButtonSprite()
{
}

void StartButtonSprite::UpdateGameObject(float _deltaTime)
{
}
