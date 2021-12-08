#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitlePlayerStateBase.h"

/*
@file TitlePlayerStateJumpStart.h
@brief �^�C�g���V�[�����ł̃W�����v�J�n��Ԃ��Ǘ�����N���X
*/
class TitlePlayerStateJumpStart :
    public TitlePlayerStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	TitlePlayerStateJumpStart()
	{};

	/*
	@fn �f�X�g���N�^
	*/
	~TitlePlayerStateJumpStart() {};

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
	// ��p����W�����v��
	float jumpPower;
	// �W�����v���Ԃ𐔂���J�E���g
	int jumpFrameCount;
	// �W�����v������
	int jumpCount;
};

