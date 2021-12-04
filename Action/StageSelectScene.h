#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "BaseScene.h"

// �N���X�̑O���錾
class StageSelectSceneSoundManager;

/*
@file StageSelectScene.h
@brief �X�e�[�W�I���V�[���̊Ǘ��ƍX�V���s��
*/
class StageSelectScene :
    public BaseScene
{
public:

	/*
	@fn �R���X�g���N�^
	@brief  Scene�̐������s��
	*/
	StageSelectScene();

	/*
	@fn �f�X�g���N�^
	@brief  scene�̍폜���s��
	*/
	~StageSelectScene()override;

	/*
	@fn     �V�[���̃A�b�v�f�[�g�֐�
	@brief	�V�[���̍X�V�������s��
	@param	���͏��
	@return �V�[���̑J�ڂ𔻒肷�邽�߂�enum�^��SceneState
	*/
	SceneState Update(const InputState& _inputState)override;

private:

	void SelectRight();
	void SelectLeft();
	void SelectAnalogStick(float _axis);

	// �A�i���O�X�e�B�b�N�ɂ��I���V�[���ύX���\���ǂ���
	bool isAnalogStickSelect;
	// �A�i���O�X�e�B�b�N�ɂ��I���̍Ďg�p�\�ɂȂ�܂ł̃J�E���g�𐔂���
	int selectCount;

	// �V�[�������肳�ꂽ���ǂ���
	bool isSceneSelect;

	// �I������Ă���V�[���X�e�[�^�X
	SceneState selectState;

	// stage�I����ʂ̃T�E���h���Ǘ����Ă���N���X
	StageSelectSceneSoundManager* stageSelectSceneSoundManager;

	// �f�b�h�X�y�[�X�萔
	const float InputDeadSpace;

public:

	SceneState GetSelectState() const { return selectState; }

};