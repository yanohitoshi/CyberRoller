//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitleSceneUI.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "TitleBackGroundSprite.h"
#include "SkyBoxObject.h"

TitleSceneUI::TitleSceneUI()
	: GameObject(false,UI)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// spriteComponent��new����
	sprite = new SpriteComponent(this, false);
	// �^�C�g����texture�����[�h
	Texture* tex = RENDERER->GetTexture("Assets/sprite/Title.png");
	// texture��Component�ɃZ�b�g
	sprite->SetTexture(tex);
	// alpha�l��������
	sprite->SetAlpha(1.0f);
	// �X�J�C�{�b�N�X�𐶐�
	skyBox = new SkyBoxObject(false, Tag::UI);
}

TitleSceneUI::~TitleSceneUI()
{
}

void TitleSceneUI::UpdateGameObject(float _deltaTime)
{
}
