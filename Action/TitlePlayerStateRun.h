#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitlePlayerStateBase.h"

/*
@file TitlePlayerStateRun.h
@brief �^�C�g���V�[�����ł̑����Ԃ��Ǘ�����N���X
*/
class TitlePlayerStateRun :
    public TitlePlayerStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	TitlePlayerStateRun()
	: JumpDelayTime(120)
	, CorrectionValuePositionY(5.0f){};

	/*
	@fn �f�X�g���N�^
	*/
	~TitlePlayerStateRun() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return TitlePlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
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
	@param	_owner �e�N���X�̃|�C���^
	*/
	void JumpDelayProcess(TitlePlayerObject* _owner);

	// �����|�W�V�����ɖ߂��Ă��Ă��邩�̔������邽�߂̒l��␳����萔
	const float CorrectionValuePositionY;
	Vector3 initPosition;
	// �W�����v�\��
	bool isAvailableJump;
	// �W�����v�҂����Ԃ𐔂���
	int jumpDelayCount;
	// �W�����v�҂�����
	const int JumpDelayTime;
	// �W�����v���Ԃ𐔂���J�E���g
	int jumpCount;
};

