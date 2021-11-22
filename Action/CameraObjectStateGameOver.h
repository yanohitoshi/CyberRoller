#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CameraObjectStateBase.h"

/*
@file CameraObjectStateGameOver.h
@brief �J�����̃Q�[���I�[�o�[��Ԃ��X�V����N���X
*/
class CameraObjectStateGameOver :
    public CameraObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	CameraObjectStateGameOver()
		: GameOverRadius(400.0f)
		, AutomaticMoveSpeed(0.01f)
		, InitYaw(180.0f) 
		, OffsetZ(600.0f){};

	/*
	@fn �f�X�g���N�^
	*/
	~CameraObjectStateGameOver() {};

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
	// �Q�[���I�[�o�[���̔��a�萔
	const float GameOverRadius;
	// ������]����ۂ̈ړ����x
	const float AutomaticMoveSpeed;
	// Z���̊Ԋu
	const float OffsetZ;
};

