#pragma once
#include "CameraObjectStateBase.h"

class CameraObjectStateDance :
    public CameraObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	CameraObjectStateDance()
	: DanceRadius(500.0f)
	, AutomaticMoveSpeed(0.01f){};

	/*
	@fn �f�X�g���N�^
	*/
	~CameraObjectStateDance() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	CameraState Update(CameraObjectBase* _owner, float _deltaTime)override;

	/*
	@fn �C���v�b�g
	@brief	state�ɉ����ē��͏������s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_keyState ���͏��
	*/
	void Input(CameraObjectBase* _owner, const InputState& _keyState)override;

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Enter(CameraObjectBase* _owner, float _deltaTime)override;
private:

	float yaw;
	const float DanceRadius;
	// ������]����ۂ̈ړ����x
	const float AutomaticMoveSpeed;
};

