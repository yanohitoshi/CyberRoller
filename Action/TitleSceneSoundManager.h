#pragma once
#include "GameObject.h"

class MusicComponent;

class TitleSceneSoundManager :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	TitleSceneSoundManager();

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~TitleSceneSoundManager()override;

	/*
	@fn �A�b�v�f�[�g�֐�
	@brief	�X�V�������s��
	@param	_deltaTime �O�̃t���[���ł�����������
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	// Mesh���Ǘ�����N���X
	MusicComponent* bgm;
};

