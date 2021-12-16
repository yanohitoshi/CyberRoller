//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameOverSprite.h"
#include "SpriteComponent.h"
#include "ContinueSprite.h"
#include "GraphicsResourceManager.h"

/*
@brief	�R���X�g���N�^
*/
GameOverSprite::GameOverSprite()
	:GameObject(false, Tag::UI)
	, DrawCount(60)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// texture�����[�h
	Texture* tex = GRAPHICS_RESOURCE->CreateTexture("Assets/sprite/information/gameover.png");
	// SpriteComponent������
	sprite = new SpriteComponent(this,false);
	sprite->SetTexture(tex);
	sprite->SetVisible(false);
	sprite->SetAlpha(1.0f);
	// �����o�[�ϐ�������
	frameCount = 0;
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
GameOverSprite::~GameOverSprite()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
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