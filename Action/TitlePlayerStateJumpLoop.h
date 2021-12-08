#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitlePlayerStateBase.h"

/*
@file TitlePlayerStateJumpLoop.h
@brief �^�C�g���V�[�����ł̃W�����v���[�v��Ԃ��Ǘ�����N���X
*/
class TitlePlayerStateJumpLoop :
    public TitlePlayerStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	TitlePlayerStateJumpLoop()
	: OnGroundCoordinate(100.0f){};

	/*
	@fn �f�X�g���N�^
	*/
	~TitlePlayerStateJumpLoop() {};

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
	// �ڒn����������W�l�萔
	const float OnGroundCoordinate;
	// �^�C�g����ʂł̃W�����v�A�^�b�N�v���C���[�N���X�̃|�C���^
	TitleJumpAttackPlayerObject* titleJumpAttackPlayerObject;
};

