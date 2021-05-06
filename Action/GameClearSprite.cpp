#include "GameClearSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "PlayerObject.h"

GameClearSprite::GameClearSprite(PlayerObject* _playerObject)
	:GameObject(false, Tag::UI)
	, DRAW_COUNT(120)
{

	playerObject = _playerObject;

	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// texture�����[�h
	Texture* tex = RENDERER->GetTexture("Assets/sprite/gameclear2.png");
	// SpriteComponent������
	sprite = new SpriteComponent(this,false);
	sprite->SetTexture(tex);
	sprite->SetVisible(false);
	sprite->SetAlpha(1.0f);
	// �����o�[�ϐ�������
	frameCount = 0;
}

GameClearSprite::~GameClearSprite()
{
}

void GameClearSprite::UpdateGameObject(float _deltaTime)
{
	// �N���A��ԂɂȂ�����
	if (playerObject->GetClearFlag() == true)
	{
		// �t���[���J�E���g�𐔂���
		++frameCount;
		// 120�J�E���g��������`�悷��
		if (frameCount >= DRAW_COUNT)
		{
			sprite->SetVisible(true);
		}
	}
}
