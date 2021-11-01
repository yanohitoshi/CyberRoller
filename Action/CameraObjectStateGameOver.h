#pragma once
#include "CameraObjectStateBase.h"

class CameraObjectStateGameOver :
    public CameraObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	CameraObjectStateGameOver()
		: GameOverRadius(400.0f)
		, AutomaticMoveSpeed(0.01f) {};

	/*
	@fn �f�X�g���N�^
	*/
	~CameraObjectStateGameOver() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	CameraState Update(CameraObjectBase* _owner, float _deltaTime)override;

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Enter(CameraObjectBase* _owner, float _deltaTime)override;

private:

	float yaw;
	const float GameOverRadius;
	// ������]����ۂ̈ړ����x
	const float AutomaticMoveSpeed;
};

