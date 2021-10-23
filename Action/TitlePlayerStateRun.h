#pragma once
#include "TitlePlayerStateBase.h"

class TitlePlayerStateRun :
    public TitlePlayerStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	TitlePlayerStateRun()
	: JumpDelayTime(120){};

	/*
	@fn �f�X�g���N�^
	*/
	~TitlePlayerStateRun() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	TitlePlayerState Update(TitlePlayerObject* _owner, float _deltaTime)override;

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Enter(TitlePlayerObject* _owner, float _deltaTime)override;

private:
	
	/*
	@fn �W�����v�f�B���C�����֐�
	*/
	void JumpDelayProcess(TitlePlayerObject* _owner);

	int jumpDelayCount;
	int jumpCount;
	const int JumpDelayTime;
};

