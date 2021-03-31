#pragma once
#include "PlayerObject.h"

class PlayerObject;

enum class PlayerState
{
	// �ҋ@
	PLAYER_STATE_IDLE = 0,
	// �W�����v�I��
	PLAYER_STATE_WALK,
	// ����
	PLAYER_STATE_RUN,
	// �W�����v���[�v
	PLAYER_STATE_JUMPLOOP, 
	// �W�����v�X�^�[�g
	PLAYER_STATE_JUMPSTART,
	// �W�����v�I��
	PLAYER_STATE_JUMPEND,
	// �R���e�j���[�I����Ԃɓ���O�̏��
	PLAYER_STATE_DOWNSTART,
	// �R���e�j���[�I�����
	PLAYER_STATE_DOWN_LOOP,
	// �R���e�j���[���
	PLAYER_STATE_DOWN_UP,
	// �Q�[���I�[�o�[���
	PLAYER_STATE_DOWN_OVER,
	// ���S���
	PLAYER_STATE_DEAD,
	// ���X�|�[�����
	PLAYER_STATE_RESPAWN,

	// ���A�j���[�V������
	PLAYER_STATE_NUM,
};

class PlayerObjectStateBase
{
public:
	
	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateBase() {}

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
	virtual PlayerState Update(PlayerObject* _owner, float _deltaTime) = 0;

	/*
	@fn �C���v�b�g
	@brief	state�ɉ����ē��͏������s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_keyState ���͏��
	*/
	virtual void Input(PlayerObject* _owner, const InputState& _keyState) {};
	
	/*
	@fn �R���X�g���N�^
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	virtual void Enter(PlayerObject* _owner, float _deltaTime) {};

protected:

	//PlayerObject* owner;
	PlayerState state;
	Vector3 velocity;

};

