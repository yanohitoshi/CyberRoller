//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ResultSceneUI.h"
#include "Renderer.h"
#include "SkyBoxObject.h"

/*
@fn �R���X�g���N�^
@brief  object�̐������s��
*/
ResultSceneUI::ResultSceneUI()
	: GameObject(false, UI)
{
	// �X�J�C�{�b�N�X�𐶐�
	skyBox = new SkyBoxObject(false, Tag::UI);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
ResultSceneUI::~ResultSceneUI()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void ResultSceneUI::UpdateGameObject(float _deltaTime)
{
}