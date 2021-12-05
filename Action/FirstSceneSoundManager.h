#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class MusicComponent;
class SoundEffectComponent;

/*
@file FirstSceneSoundManager.h
@brief ���X�e�[�W�V�[���̃T�E���h���Ǘ�����N���X
*/
class FirstSceneSoundManager :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	@param �e�N���X�̃V�[���N���X�̃|�C���^
	*/
	FirstSceneSoundManager(BaseScene* _owner);

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~FirstSceneSoundManager()override;

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
	// �Q�[���I�[�o�[BGM
	MusicComponent* gameOverBgm;
	// �J�E���g�_�E���T�E���h�G�t�F�N�g
	SoundEffectComponent* countDown;
	// �R���e�B�j���[�T�E���h�G�t�F�N�g
	SoundEffectComponent* continueSound;
	// �Q�[���I���T�E���h�G�t�F�N�g
	SoundEffectComponent* gameEnd;

	// �J�E���g�_�E������炷���ǂ���
	bool isCountDownPlay;
	// BGM���؂�ւ���ꂽ���ǂ���
	bool isbgmChanged;

	// �R���e�B�j���[�T�E���h�G�t�F�N�g���Đ����邩�ǂ���
	bool isPlayContinue;
	// �Q�[���I���T�E���h�G�t�F�N�g���Đ����邩�ǂ���
	bool isPlayGameEnd;
};

