//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitleSceneUI.h"
#include "RenderingObjectManager.h"
#include "SpriteComponent.h"
#include "TitleSprite.h"
#include "StartButtonSprite.h"
#include "SkyBoxObject.h"

/*
@fn �R���X�g���N�^
@brief  object�̐������s��
*/
TitleSceneUI::TitleSceneUI()
	: GameObject(false,UI)
{
	new TitleSprite();
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