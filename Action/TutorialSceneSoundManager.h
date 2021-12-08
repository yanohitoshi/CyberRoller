#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class MusicComponent;
class SoundEffectComponent;

/*
@file TutorialSceneSoundManager .h
@brief �`���[�g���A���X�e�[�W�V�[���̃T�E���h���Ǘ�����N���X
*/
class TutorialSceneSoundManager :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param �e�N���X�̃V�[���N���X�̃|�C���^
	*/
	TutorialSceneSoundManager(BaseScene* _owner);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~TutorialSceneSoundManager()override;

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// �I�[�i�[�N���X�̃|�C���^
	BaseScene* owner;

	// BGM���Ǘ�����N���X
	MusicComponent* bgm;
	SoundEffectComponent* countDown;

	// �J�E���g�_�E������炷���ǂ���
	bool isCountDownPlay;
};

