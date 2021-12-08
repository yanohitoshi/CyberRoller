#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateJumpAttackEnd.h
@brief �W�����v�U���I������A�C�h�����O�Ɉڍs����܂ł��Ǘ�
*/
class PlayerObjectStateJumpAttackEnd :
    public PlayerObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	@param _owner �e�N���X�̃|�C���^
	*/
	PlayerObjectStateJumpAttackEnd(PlayerObject* _owner);

	/*
	@fn �f�X�g���N�^
	*/
	~PlayerObjectStateJumpAttackEnd()override;

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	PlayerState Update(PlayerObject* _owner, float _deltaTime)override;

	/*
	@fn �C���v�b�g
	@brief	state�ɉ����ē��͏������s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_keyState ���͏��
	*/
	void Input(PlayerObject* _owner, const InputState& _keyState)override;

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Enter(PlayerObject* _owner, float _deltaTime)override;

private:

	// �W�����v���s���Ă���t���[���𑪂�J�E���g�ϐ�
	int jumpFrameCount;
	// �W�����v���I���������ǂ����̃t���O�ϐ�
	bool endFlag;

	// �X�C�b�`�W�����v���̃W�����v�͂̉����x
	const float SuccessJumpAccelPower;
	// �X�C�b�`�W�����v���p�\�^�C��
	const int SuccessJumpTime;
	// �W�����v�A�^�b�N�������̏���
	const float JumpAttackSuccessFirstPower;
};