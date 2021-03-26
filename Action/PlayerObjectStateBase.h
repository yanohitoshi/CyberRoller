#pragma once
#include "PlayerObject.h"

enum class PlayerState
{
	// �ҋ@
	PLAYER_STATE_IDLE = 0,
	// ����
	PLAYER_STATE_RUN,
	// �W�����v�X�^�[�g
	PLAYER_STATE_JUMPSTART,
	// �W�����v���[�v
	PLAYER_STATE_JUMPLOOP,    
	// �W�����v�I��
	PLAYER_STATE_JUMPEND,
	// ���A�j���[�V������
	PLAYER_STATE_NUM,
};

class PlayerObjectStateBase
{
public:
	
	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateBase(PlayerObject* _owner) { owner = _owner; }

	/*
	@fn �f�X�g���N�^
	*/
	virtual ~PlayerObjectStateBase() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	virtual PlayerState Update(float _deltaTime) {};

	/*
	@fn �C���v�b�g
	@brief	state�ɉ����ē��͏������s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_keyState ���͏��
	*/
	virtual void Input(const InputState& _keyState) {};
	
	/*
	@fn �R���X�g���N�^
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	virtual void Enter(float _deltaTime) {};

protected:

	PlayerObject* owner;
	PlayerState state;
	Vector3 velocity;

};

