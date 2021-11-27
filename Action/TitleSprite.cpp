//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitleSprite.h"
#include "RenderingObjectManager.h"
#include "SpriteComponent.h"

/*
@fn �R���X�g���N�^
*/
TitleSprite::TitleSprite()
	:GameObject(false, Tag::UI)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 300.0f, 0.0f));
	SetScale(Vector3(0.2f, 0.2f, 0.2f));
	// spriteComponen��new����
	sprite = new SpriteComponent(this, false);
	// �w�i�e�N�X�`�������[�h
	Texture* tex = RENDERING_OBJECT_MANAGER->GetTexture("Assets/sprite/title/Title.png");
	// �w�i�e�N�X�`�����Z�b�g
	sprite->SetTexture(tex);
	// �f���f���Ȃ����Z�b�g
	sprite->SetVisible(true);
	// alpha�l���Z�b�g
	sprite->SetAlpha(1.0f);

}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
TitleSprite::~TitleSprite()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void TitleSprite::UpdateGameObject(float _deltaTime)
{
}