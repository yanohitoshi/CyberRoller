#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitlePlayerStateBase.h"

/*
@file TitlePlayerStateJumpAttack.h
@brief �^�C�g���V�[�����ł̃W�����v�A�^�b�N��Ԃ��Ǘ�����N���X
*/
class TitlePlayerStateJumpAttack :
    public TitlePlayerStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	TitlePlayerStateJumpAttack()
	: JumpAttackRotationAngle(10.0f)
	, JumpAttackTime(30)
	, ShiftPositionZ(100.0f)
	, Offset(400.0f){};

	/*
	@fn �f�X�g���N�^
	*/
	~TitlePlayerStateJumpAttack() {};

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

	// �^�C�g����ʂł̃W�����v�A�^�b�N�v���C���[�N���X�̃|�C���^
	TitleJumpAttackPlayerObject* titleJumpAttackPlayerObject;

	// state�ɓ����Ă����Ƃ��̃|�W�V����
	Vector3 enterPosition;
	// ��]�p�x
	float rotationAngle;
	// �t���[�����Ԃ𐔂���J�E���g
	int frameCount;
	// �Ԋu
	const float Offset;
	// �W�����v�U�����鎞��
	const int JumpAttackTime;
	// ��]�p�萔
	const float JumpAttackRotationAngle;
	// Z�������炷���߂̒萔
	const float ShiftPositionZ;
};

