#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

// �N���X�̑O���錾
class SkeletalMeshComponent;

/*
@file PlayerObjectStateJumpLoop.h
@brief �W�����v���[�v��Ԃ��Ǘ�
*/
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

	/*
	@fn ���̓`�F�b�N�֐������֐�
	@param	_owner �e�N���X�̃|�C���^
	*/
	void ChackInputProcess(PlayerObject* _owner, const InputState& _keyState);

	/*
	@fn ���͂�����ꍇ�̏����֐�
	@param	_owner �e�N���X�̃|�C���^
	@param	_keyState ���͏��
	@param	_axis �␳�ς݂̃A�i���O�X�e�B�b�N���
	*/
	void InputMovableProcess(PlayerObject* _owner, const InputState& _keyState, Vector3 _axis);

	/*
	@fn ���͂��Ȃ��ꍇ�̏����֐�
	@param	_owner �e�N���X�̃|�C���^
	*/
	void UninputMovableProcess(PlayerObject* _owner);

	// �W�����v���[�v���s���Ă��鎞�Ԃ𑪂�J�E���g�ϐ�
	int jumpLoopCount;
	// �W�����v�X�^�[�g�̃A�j���[�V�������I������^�C�~���O�����炷���߂̃t���O
	// �������ڏジ�炵���������̂ō��܂���
	bool animChangeFlag;

	// ���n���]���[�V�������܂߂邩���肷�鑬�x�萔
	const float TurnValue;

	// �W�����v���Ɉړ����x�����X�Ɍ��炷���߂̌v�Z�Ɏg���␳�l
	const float JumpCorrection;
	// �X�C�b�`�W�����v���Ɉړ����x�����X�Ɍ��炷���߂̌v�Z�Ɏg���␳�l
	const float SwitchJumpCorrection;
};

