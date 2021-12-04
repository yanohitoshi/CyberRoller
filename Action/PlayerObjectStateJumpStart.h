#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

// �N���X�̑O���錾
class SkeletalMeshComponent;

/*
@file PlayerObjectStateJumpStart.h
@brief �W�����v�J�n��Ԃ��Ǘ�
*/
class PlayerObjectStateJumpStart :
    public PlayerObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateJumpStart(PlayerObject* _owner);

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

	/*
	@fn ���̓`�F�b�N�֐������֐�
	@param	_owner �e�N���X�̃|�C���^
	@param	_keyState ���͏��
	*/
	void CheckInputProcess(PlayerObject* _owner, const InputState& _keyState);

	/*
	@fn ���͂��Ȃ��ꍇ�̏����֐�
	@param	_owner �e�N���X�̃|�C���^
	*/
	void UninputMovableProcess(PlayerObject* _owner);

	/*
	@fn �W�����v�J�n�����֐�
	@param	_owner �e�N���X�̃|�C���^
	*/
	void JumpStartProcess(PlayerObject* _owner);

	/*
	@fn �W�����v�I�����������֐�
	@param	_owner �e�N���X�̃|�C���^
	*/
	void JumpEndProcess(PlayerObject* _owner);

	// �W�����v���s���Ă���t���[���𑪂�J�E���g�ϐ�
	int jumpFrameCount;
	// �W�����v���I���������ǂ����̃t���O�ϐ�
	bool endFlag;
	// �W�����v���Ɉړ����x�����X�Ɍ��炷���߂̌v�Z�Ɏg���␳�l
	const float JumpCorrection;
	// �X�C�b�`�W�����v���Ɉړ����x�����X�Ɍ��炷���߂̌v�Z�Ɏg���␳�l
	const float SwitchJumpCorrection;
	// �W�����v�͂̉����x
	const float JumpAccelPower;
	// �X�C�b�`�W�����v���̃W�����v�͂̉����x
	const float SwitchJumpAccelPower;
	// �W�����v�{�^�����p�\�^�C��
	const int JumpTime;
	// �X�C�b�`�W�����v���p�\�^�C��
	const int SwitchJumpTime;
	// ���������ɃI�[�i�[�̑��x�Ɍ������|����萔
	const float Deceleration;

	// �X�e�[�^�X���؂�ւ�������ɖ炷�T�E���h�G�t�F�N�g�N���X
	SoundEffectComponent* switchJumpSoundEffect;
};

