#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class MusicComponent;
class SoundEffectComponent;

/*
@file TitleSceneSoundManager.h
@brief �^�C�g���V�[���̃T�E���h���Ǘ�����N���X
*/
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

	/*
	@fn ���͂������Ŏ󂯎��X�V�֐�
	@brief ��{�I�ɂ����œ��͏���ϐ��ɕۑ���UpdateGameObject�ōX�V���s��
	@param	_keyState ���͏��
	*/
	void GameObjectInput(const InputState& _keyState);

private:

	// Mesh���Ǘ�����N���X
	MusicComponent* bgm;
	SoundEffectComponent* startSceneSound;
	// ����{�^���������ꂽ���ǂ���
	bool isPushDecisionSceneButton;
	// ���͂����p�\���ǂ���
	bool isAvailableSelectInput;

	// stage���莞�̃T�E���h���Ȃ�I��������ǂ���
	bool isPlayDecisionSound;

public:
	
	/*
	@brief	stage���莞�̃T�E���h���Ȃ�I��������ǂ������擾
	@return	isEndDecisionSound stage���莞�̃T�E���h�̍Đ����I��������ǂ���
	*/
	bool GetIsPlayDecisionSound() { return isPlayDecisionSound; }
};

