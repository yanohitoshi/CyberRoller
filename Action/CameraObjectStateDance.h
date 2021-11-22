#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CameraObjectStateBase.h"

/*
@file CameraObjectStateDance.h
@brief �J�����̃_���X��Ԃ̍X�V���s���N���X
*/
class CameraObjectStateDance :
    public CameraObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	CameraObjectStateDance()
	: DanceRadius(500.0f)
	, AutomaticMoveSpeed(0.01f)
	, InitYaw(180.0f)
	, OffsetZ(600.0f){};

	/*
	@fn �f�X�g���N�^
	*/
	~CameraObjectStateDance() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return CameraState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	CameraState Update(CameraObjectBase* _owner, float _deltaTime)override;

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Enter(CameraObjectBase* _owner, float _deltaTime)override;

private:

	// ���[�ϐ�
	float yaw;
	// �X�e�[�^�X�J�n���̃��[�̒l�萔
	const float InitYaw;
	// �_���X���̔��a�萔
	const float DanceRadius;
	// ������]����ۂ̈ړ����x
	const float AutomaticMoveSpeed;
	// Z���̊Ԋu
	const float OffsetZ;
};

