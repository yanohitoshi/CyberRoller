#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "BaseScene.h"
#include "GameObject.h"

class MusicComponent;
class TitleSceneSoundManager;
/*
@file TitleScene.h
@brief �^�C�g���V�[���̊Ǘ��ƍX�V���s��
*/
class TitleScene : public BaseScene
{
public:

	/*
	@fn �R���X�g���N�^
	@brief  Scene�̐������s��
	*/
	TitleScene();

	/*
	@fn �f�X�g���N�^
	@brief  scene�̍폜���s��
	*/
	~TitleScene()override;

	/*
	@fn     �V�[���̃A�b�v�f�[�g�֐�
	@brief	�V�[���̍X�V�������s��
	@param	���͏��
	@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
	*/
	SceneState Update(const InputState& _inputState)override;

private:

	TitleSceneSoundManager* titleSceneSoundManager;

	// �V�[�������肳�ꂽ���ǂ���
	bool isGameStart;
};