#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObjectStateJumpEnd :
    public PlayerObjectStateBase
{
public:
	
	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateJumpEnd();

	/*
	@fn �f�X�g���N�^
	*/
	~PlayerObjectStateJumpEnd()override;

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
	@fn �R���X�g���N�^
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Enter(PlayerObject* _owner, float _deltaTime)override;

};

