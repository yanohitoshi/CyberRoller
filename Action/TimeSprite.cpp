//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TimeSprite.h"
#include "RenderingObjectManager.h"
#include "SpriteComponent.h"
#include "CountDownFont.h"

/*
@brief	�R���X�g���N�^
*/
TimeSprite::TimeSprite()
	: GameObject(false, Tag::UI)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(700.0f, 480.0f, 0.0f));
	// SpriteComponent������
	sprite = new SpriteComponent(this, false);
	tex = RENDERING_OBJECT_MANAGER->CreateTexture("Assets/sprite/time/Time_UI.png");
	sprite->SetTexture(tex);
	sprite->SetAlpha(1.0f);
	// �����o�[�ϐ�������
	frameCount = 0;
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
TimeSprite::~TimeSprite()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void TimeSprite::UpdateGameObject(float _deltaTime)
{
	// �^�C���I�[�o�[�ɂȂ�����`���؂�
	if (CountDownFont::GetTimeOverFlag() == true)
	{
		sprite->SetVisible(false);
	}
}