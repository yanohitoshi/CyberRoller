#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "BaseScene.h"


/*
@file FirstStageScene.h
@brief ���X�e�[�W(�`���[�g���A��)�̏������Ɛ����A���̃V�[���ւ̃V�[���J�ڂ��s��
*/
class FirstStageScene : public BaseScene
{
public:
	/*
	@fn �R���X�g���N�^
	@brief  Scene�̐������s��
	*/
	FirstStageScene();
	
	/*
	@fn �f�X�g���N�^
	@brief  scene�̍폜���s��
	*/
	~FirstStageScene()override;

	/*
	@fn�@�V�[���̃A�b�v�f�[�g�֐�
	@brief	�V�[���̍X�V�������s��
	@param	���͏��
	@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
	*/
	SceneState Update(const InputState& state)override;

private:

};

