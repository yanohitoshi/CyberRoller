#pragma once
#include "CameraObjectBase.h"

enum class CameraState
{
	NORMAL,
	LANDSCAPE,
	DANCE,
	GAMEOVER,
	SCENECLEAR,
	NONE
};

class CameraObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	CameraObjectStateBase()
	: DeltaCorrection(8.0f){};

	/*
	@fn �f�X�g���N�^
	*/
	virtual ~CameraObjectStateBase() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	virtual CameraState Update(CameraObjectBase* _owner, float _deltaTime) = 0;

	/*
	@fn �C���v�b�g
	@brief	state�ɉ����ē��͏������s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_keyState ���͏��
	*/
	virtual void Input(CameraObjectBase* _owner, const InputState& _keyState) {};

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	virtual void Enter(CameraObjectBase* _owner, float _deltaTime) {};

protected:

	// ���`�ۊǎ��Ƀf���^�^�C����������Ƃ��p�̕␳�萔
	const float DeltaCorrection;
	CameraState state;
	Vector3 offsetPosition;
};

