#pragma once
#include "GameObject.h"

class MusicComponent;
class SoundEffectComponent;

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

	BaseScene* owner;

	// BGM���Ǘ�����N���X
	MusicComponent* bgm;
	SoundEffectComponent* changeSelectSceneSound;
	SoundEffectComponent* sceneDecisionSound;

	bool isAnalogStickSelect;
	int selectCount;

	// stage���莞�̃T�E���h���Ȃ�I��������ǂ���
	bool isEndDecisionSound;

	// �f�b�h�X�y�[�X�萔
	const float InputDeadSpace;

public:

	/*
	@brief	stage���莞�̃T�E���h���Ȃ�I��������ǂ������擾
	@return	isEndDecisionSound stage���莞�̃T�E���h���Ȃ�I��������ǂ���
	*/
	bool GetIsEndDecisionSound() { return isEndDecisionSound; }

};

