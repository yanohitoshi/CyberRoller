#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateJumpEndToIdle.h
@brief �W�����v�I������A�C�h�����O�Ɉڍs����܂ł��Ǘ�
*/
class PlayerObjectStateJumpEndToIdle :
    public PlayerObjectStateBase
{
public:
	
	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateJumpEndToIdle(PlayerObject* _owner);

	/*
	@fn �f�X�g���N�^
	*/
	~PlayerObjectStateJumpEndToIdle()override;

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

};

