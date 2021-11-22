//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameClearSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "PlayerObject.h"

/*
@brief	�R���X�g���N�^
@param	_playerObject �v���C���[�I�u�W�F�N�g�̃|�C���^
*/
GameClearSprite::GameClearSprite(PlayerObject* _playerObject)
	:GameObject(false, Tag::UI)
	, DrawCount(120)
{

	playerObject = _playerObject;

	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// texture�����[�h
	Texture* tex = RENDERER->GetTexture("Assets/sprite/information/gameclear.png");
	// SpriteComponent������
	sprite = new SpriteComponent(this,false);
	sprite->SetTexture(tex);
	sprite->SetVisible(false);
	sprite->SetAlpha(1.0f);
	SetScale(1.5f);
	// �����o�[�ϐ�������
	frameCount = 0;
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
GameClearSprite::~GameClearSprite()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void GameClearSprite::UpdateGameObject(float _deltaTime)
{
	// �N���A��ԂɂȂ�����
	if (playerObject->GetClearFlag() == true)
	{
		// �t���[���J�E���g�𐔂���
		++frameCount;
		// 120�J�E���g��������`�悷��
		if (frameCount >= DrawCount)
		{
			sprite->SetVisible(true);
		}
	}
}