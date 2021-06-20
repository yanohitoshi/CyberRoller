#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateRunTurn.h
@brief �����Ԃ���̐؂�ւ������Ǘ�
*/
class PlayerObjectStateRunTurn :
    public PlayerObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateRunTurn();

	/*
	@fn �f�X�g���N�^
	*/
	~PlayerObjectStateRunTurn()override;

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
	@param	_axis �␳�ς݂̃A�i���O�X�e�B�b�N���
	*/
	void InputMovableProcess(PlayerObject* _owner, Vector3 _axis);

	/*
	@fn ���͂��Ȃ��ꍇ�̏����֐�
	@param	_owner �e�N���X�̃|�C���^
	*/
	void UninputMovableProcess(PlayerObject* _owner);

	/*
	@fn �W�����v��ԂɑJ�ڂ��邽�߂̏��������֐�
	@param	_owner �e�N���X�̃|�C���^
	*/
	void JumpTransitionProcess(PlayerObject* _owner);

	// ������
	float decelerationForce;
	// �^�[����Ԃ��瑖���Ԃɓ���ۂ̍Œᑬ�x
	const float MinimumSpeed;

};

