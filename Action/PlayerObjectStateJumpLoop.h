#pragma once
#include "PlayerObjectStateBase.h"

class SkeletalMeshComponent;

class PlayerObjectStateJumpLoop :
    public PlayerObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateJumpLoop();

	/*
	@fn �f�X�g���N�^
	*/
	~PlayerObjectStateJumpLoop()override;

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

	// �W�����v���[�v���s���Ă��鎞�Ԃ𑪂�J�E���g�ϐ�
	int jumpLoopCount;
	// �W�����v�X�^�[�g�̃A�j���[�V�������I������^�C�~���O�����炷���߂̃t���O
	// �������ڏジ�炵���������̂ō��܂���
	bool animChangeFlag;

	// �������x�̋K��l
	const float MaxFallSpeed;

	// ���n���]���[�V�������܂߂邩���肷�鑬�x�萔
	const float TurnValue;

	// �W�����v���Ɉړ����x�����X�Ɍ��炷���߂̌v�Z�Ɏg���␳�l
	const float JumpCorrection;
	// �X�C�b�`�W�����v���Ɉړ����x�����X�Ɍ��炷���߂̌v�Z�Ɏg���␳�l
	const float SwitchJumpCorrection;
};

