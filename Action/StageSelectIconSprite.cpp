#include "StageSelectIconSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"

StageSelectIconSprite::StageSelectIconSprite(Vector3& _pos, const std::string& _spriteFileName)
	: GameObject(false, Tag::UI)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, -300.0f, 0.0f));
	SetPosition(_pos);
	SetScale(Vector3(0.25f, 0.25f, 0.25f));
	// spriteComponen��new����
	sprite = new SpriteComponent(this, false);
	// �w�i�e�N�X�`�������[�h
	Texture* tex = RENDERER->GetTexture(_spriteFileName);
	// �w�i�e�N�X�`�����Z�b�g
	sprite->SetTexture(tex);
	// �f���f���Ȃ����Z�b�g
	sprite->SetVisible(true);
	// alpha�l���Z�b�g
	sprite->SetAlpha(1.0f);
}

StageSelectIconSprite::~StageSelectIconSprite()
{
}

void StageSelectIconSprite::UpdateGameObject(float _deltaTime)
{
}
