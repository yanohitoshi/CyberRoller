//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitleSceneUI.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "StartButtonSprite.h"
#include "SkyBoxObject.h"

/*
@fn �R���X�g���N�^
@brief  object�̐������s��
*/
TitleSceneUI::TitleSceneUI()
	: GameObject(false,UI)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 300.0f, 0.0f));
	SetScale(Vector3(0.2f, 0.2f, 0.2f));
	// spriteComponent��new����
	sprite = new SpriteComponent(this, false);
	// �^�C�g����texture�����[�h
	Texture* tex = RENDERER->GetTexture("Assets/sprite/Title_test.png");
	// texture��Component�ɃZ�b�g
	sprite->SetTexture(tex);
	// alpha�l��������
	sprite->SetAlpha(1.0f);
	new StartButtonSprite();
	// �X�J�C�{�b�N�X�𐶐�
	skyBox = new SkyBoxObject(false, Tag::UI);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
TitleSceneUI::~TitleSceneUI()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void TitleSceneUI::UpdateGameObject(float _deltaTime)
{
}