#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GameObject.h"

// �N���X�̑O���錾
class MusicComponent;
class SoundEffectComponent;

/*
@file StageSelectSceneSoundManager.h
@brief �X�e�[�W�I���V�[���̃T�E���h���Ǘ�����N���X
*/
class StageSelectSceneSoundManager :
    public GameObject
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	StageSelectSceneSoundManager();

	/*
	@fn �f�X�g���N�^
	@brief  object�̍폜���s��
	*/
	~StageSelectSceneSoundManager()override;

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

	// �I�[�i�[�N���X�̃|�C���^
	BaseScene* owner;

	// BGM���Ǘ�����N���X
	MusicComponent* bgm;
	SoundEffectComponent* changeSelectSceneSound;
	SoundEffectComponent* sceneDecisionSound;

	// �A�i���O�X�e�B�b�N�ɂ��I���V�[���ύX���\���ǂ���
	bool isAnalogStickSelect;
	// �A�i���O�X�e�B�b�N�ɂ��I���̍Ďg�p�\�ɂȂ�܂ł̃J�E���g�𐔂���
	int selectCount;

	// ����{�^���������ꂽ���ǂ���
	bool isPushDecisionSceneButton;
	// ���͂����p�\���ǂ���
	bool isAvailableSelectInput;

	// stage���莞�̃T�E���h���Ȃ�I��������ǂ���
	bool isPlayDecisionSound;

	// �f�b�h�X�y�[�X�萔
	const float InputDeadSpace;
	// �A���ŃX�e�[�W�̑I�����؂�ւ��Ȃ��悤�ɂ��邽�߂̑҂����Ԓ萔
	const int SelectDelay;

public:

	/*
	@brief	stage���莞�̃T�E���h���Ȃ�I��������ǂ������擾
	@return	isEndDecisionSound stage���莞�̃T�E���h�̍Đ����I��������ǂ���
	*/
	bool GetIsPlayDecisionSound() { return isPlayDecisionSound; }
};

