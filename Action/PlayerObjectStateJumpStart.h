#pragma once
#include "PlayerObjectStateBase.h"

class SkeletalMeshComponent;

class PlayerObjectStateJumpStart :
    public PlayerObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateJumpStart();

	/*
	@fn �f�X�g���N�^
	*/
	~PlayerObjectStateJumpStart()override;

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
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
	// �������x�̋K��l
	const float MaxFallSpeed;
	// �W�����v���Ɉړ����x�����X�Ɍ��炷���߂̌v�Z�Ɏg���␳�l
	const float JumpCorrection;
	// �X�C�b�`�W�����v���Ɉړ����x�����X�Ɍ��炷���߂̌v�Z�Ɏg���␳�l
	const float SwitchJumpCorrection;
	// �W�����v�͂̉����x
	const float JumpAccelPower;
	// �W�����v�{�^�����p�\�^�C��
	const int JumpTime;
	// �X�C�b�`�W�����v���p�\�^�C��
	const int SwitchJumpTime;
};

