#pragma once
#include "TitlePlayerStateBase.h"
class TitlePlayerStateJumpAttack :
    public TitlePlayerStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	TitlePlayerStateJumpAttack()
	: JumpAttackRotationAngle(10.0f)
	, JumpAttackTime(10){};

	/*
	@fn �f�X�g���N�^
	*/
	~TitlePlayerStateJumpAttack() {};

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

	float rotationAngle;
	int frameCount;
	const int JumpAttackTime;
	// ��]�p�萔
	const float JumpAttackRotationAngle;
};

