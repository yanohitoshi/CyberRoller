#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "BaseScene.h"

// �N���X�̑O���錾
class ClearSceneUI;

/*
@file ClearScene.h
@brief �N���A�V�[���̏������Ɛ����A���̃V�[���ւ̃V�[���J�ڂ��s��
*/
class ClearScene : public BaseScene
{
public:
	/*
	@fn �R���X�g���N�^
	@brief  Scene�̐������s��
	*/
	ClearScene();
	
	/*
	@fn �f�X�g���N�^
	@brief  scene�̍폜���s��
	*/
	~ClearScene()override;

	/*
	@fn�@�V�[���̃A�b�v�f�[�g�֐�
	@brief	�V�[���̍X�V�������s��
	@param	���͏��
	@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
	*/
	SceneState Update(const InputState& state)override;

private:

};

