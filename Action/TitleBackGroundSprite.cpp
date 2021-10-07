//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitleBackGroundSprite.h"
#include "Renderer.h"
#include "SpriteComponent.h"

/*
@fn �R���X�g���N�^
*/
TitleBackGroundSprite::TitleBackGroundSprite()
	:GameObject(false, Tag::UI)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// spriteComponen��new����
	sprite = new SpriteComponent(this, true);
	// �w�i�e�N�X�`�������[�h
	Texture* tex = RENDERER->GetTexture("Assets/sprite/BackGround_SP/TitleBackGround_1.png");
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
TitleBackGroundSprite::~TitleBackGroundSprite()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void TitleBackGroundSprite::UpdateGameObject(float _deltaTime)
{
}