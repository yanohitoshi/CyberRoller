#pragma once
#include "GameObject.h"

class MusicComponent;
class SoundEffectComponent;

class FirstSceneSoundManager :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
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

	BaseScene* owner;

	// BGM���Ǘ�����N���X
	MusicComponent* bgm;
	SoundEffectComponent* countDown;

	// �J�E���g�_�E������炷���ǂ���
	bool isCountDownPlay;

};

