#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "BaseScene.h"

/*
@file FinalStageScene.h
@brief �ŏI�X�e�[�W�̊Ǘ��ƍX�V���s��
*/
class FinalStageScene :
    public BaseScene
{
public:

	/*
	@fn �R���X�g���N�^
	@brief  Scene�̐������s��
	*/
	FinalStageScene();
	
	/*
	@fn �f�X�g���N�^
	@brief  scene�̍폜���s��
	*/
	~FinalStageScene()override;

	/*
	@fn�@�V�[���̃A�b�v�f�[�g�֐�
	@brief	�V�[���̍X�V�������s��
	@param	���͏��
	@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
	*/
	SceneState Update(const InputState& _inputState)override;

private:

	// �N���A�������̃V�[�����J�ڂ���܂ł̃J�E���g
	// �ŏI�X�e�[�W�̂݉��o�������̂ŕʂŒ�`
	const int FinalClearToChangeScene;
};