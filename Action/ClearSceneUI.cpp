//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ClearSceneUI.h"
#include "Renderer.h"
#include "SpriteComponent.h"

/*
@fn �R���X�g���N�^
@brief  object�̐������s��
*/
ClearSceneUI::ClearSceneUI()
	: GameObject(false,UI)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// spriteComponent��new�Z�b�g
	sprite = new SpriteComponent(this, false);
	// �^�C�g����texture�����[�h
	Texture* tex = RENDERER->GetTexture("Assets/sprite/GameClear.png");
	// texture��Component�ɃZ�b�g
	sprite->SetTexture(tex);
	// alpha�l��������
	sprite->SetAlpha(1.0f);

}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
ClearSceneUI::~ClearSceneUI()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void ClearSceneUI::UpdateGameObject(float _deltaTime)
{
}