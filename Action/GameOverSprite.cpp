//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameOverSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "ContinueSprite.h"

GameOverSprite::GameOverSprite()
	:GameObject(false, Tag::UI)
	, DrawCount(60)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// texture�����[�h
	Texture* tex = RENDERER->GetTexture("Assets/sprite/gameover.png");
	// SpriteComponent������
	sprite = new SpriteComponent(this,false);
	sprite->SetTexture(tex);
	sprite->SetVisible(false);
	sprite->SetAlpha(1.0f);
	// �����o�[�ϐ�������
	frameCount = 0;
}

GameOverSprite::~GameOverSprite()
{
}

void GameOverSprite::UpdateGameObject(float _deltaTime)
{
	// �R���e�j���[�I����Ԃ̎��R���e�j���[���I������Ȃ�������
	if (ContinueSprite::GetDrawFlag() == false && ContinueSprite::GetContinueFlag() == false)
	{
		// �t���[���J�E���g�𐔂���
		++frameCount;
		// �J�E���g��60�ɂȂ�����`�悷��
		if (frameCount >= DrawCount)
		{
			sprite->SetVisible(true);
		}
	}
}
