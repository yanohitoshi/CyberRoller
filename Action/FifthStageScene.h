#pragma once
#include "BaseScene.h"

class FifthStageScene :
    public BaseScene
{
public:

	/*
	@fn �R���X�g���N�^
	@brief  Scene�̐������s��
	*/
	FifthStageScene();

	/*
	@fn �f�X�g���N�^
	@brief  scene�̍폜���s��
	*/
	~FifthStageScene()override;

	/*
	@fn�@�V�[���̃A�b�v�f�[�g�֐�
	@brief	�V�[���̍X�V�������s��
	@param	���͏��
	@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
	*/
	SceneState Update(const InputState& _inputState)override;

private:

};

