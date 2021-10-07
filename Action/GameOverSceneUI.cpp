//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameOverSceneUI.h"
#include "Renderer.h"
#include "SpriteComponent.h"

/*
@fn �R���X�g���N�^
@brief  object�̐������s��
*/
GameOverSceneUI::GameOverSceneUI()
	: GameObject(false, UI)
{
	// �|�W�V�������Z�b�g
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// spriteComponent��new
	sprite = new SpriteComponent(this, false);
	// �Q�[���I�[�o�[��texture�����[�h
	Texture* tex = RENDERER->GetTexture("Assets/sprite/GameOver.png");
	// texture��Component�ɃZ�b�g
	sprite->SetTexture(tex);
	// alpha�l��������
	sprite->SetAlpha(1.0f);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
GameOverSceneUI::~GameOverSceneUI()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void GameOverSceneUI::UpdateGameObject(float _deltaTime)
{
}