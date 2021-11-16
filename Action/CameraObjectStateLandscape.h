#pragma once
#include "CameraObjectStateBase.h"

class CameraObjectStateLandscape :
    public CameraObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	CameraObjectStateLandscape()
	: SlowLrapTime(80){};

	/*
	@fn �f�X�g���N�^
	*/
	~CameraObjectStateLandscape() {};

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

	// �X�e�[�^�X�J�n�ȍ~�̃J�E���g�𐔂���
	int startStateCount;
	const int SlowLrapTime;
};

