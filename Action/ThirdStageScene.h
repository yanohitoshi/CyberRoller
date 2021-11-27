#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "BaseScene.h"

/*
@file ThirdStageScene.h
@brief ��3�X�e�[�W�V�[���̊Ǘ��ƍX�V���s��
*/
class ThirdStageScene :
    public BaseScene
{
public:

	/*
	@fn �R���X�g���N�^
	@brief  Scene�̐������s��
	*/
	ThirdStageScene();

	/*
	@fn �f�X�g���N�^
	@brief  scene�̍폜���s��
	*/
	~ThirdStageScene()override;

	/*
	@fn�@�V�[���̃A�b�v�f�[�g�֐�
	@brief	�V�[���̍X�V�������s��
	@param	���͏��
	@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
	*/
	SceneState Update(const InputState& _inputState)override;

private:

};