#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "CameraObjectStateBase.h"

/*
@file CameraObjectStateChangeMode.h
@brief �J�����̉�p�ύX���[�h���X�V����N���X
*/
class CameraObjectStateChangeMode :
    public CameraObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	CameraObjectStateChangeMode()
	: SlowLrapTime(80)
	, SlowLrapCorrection(2.0f){};

	/*
	@fn �f�X�g���N�^
	*/
	~CameraObjectStateChangeMode() {};

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

	// �X�e�[�^�X�J�n�ȍ~�̃J�E���g�𐔂���
	int startStateCount;
	// ���`��Ԃ̐��l������������
	const int SlowLrapTime;
	// ���`��Ԃ̐��l�����������Ԃ̎��ɗp����␳�l�萔
	const float SlowLrapCorrection;
};

