#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateDownLoop.h
@brief �_�E�����[�v��Ԃ��Ǘ�
*/
class PlayerObjectStateDownLoop :
    public PlayerObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateDownLoop();

	/*
	@fn �f�X�g���N�^
	*/
	~PlayerObjectStateDownLoop()override;

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
	@fn �R���e�B�j���[�m�F�����֐�
	*/
	void ChackContinueProcess();

	// �R���e�B�j���[���邩�ǂ����̃t���O�ϐ�
	bool isContinue;
	// �_�E�����[�v���ɓ��͂����������ǂ����̃t���O�ϐ�
	bool isInput;
};

