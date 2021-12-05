#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "BaseScene.h"

// �N���X�̑O���錾
class ResultSceneSoundManager;

/*
@file ResultScene.h
@brief ���U���g�V�[���̊Ǘ��ƍX�V���s��
*/
class ResultScene :
    public BaseScene
{
public:
	/*
	@fn �R���X�g���N�^
	@brief  Scene�̐������s��
	*/
	ResultScene();
	
	/*
	@fn �f�X�g���N�^
	@brief  scene�̍폜���s��
	*/
	~ResultScene()override;

	/*
	@fn�@�V�[���̃A�b�v�f�[�g�֐�
	@brief	�V�[���̍X�V�������s��
	@param	���͏��
	@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
	*/
	SceneState Update(const InputState& _inputState)override;

private:

	ResultSceneSoundManager* resultSceneSoundManager;

	bool isSceneEnd;
};