#pragma once
#include "PlayerObject.h"

class PlayerObject;
class SkeletalMeshComponent;

enum class PlayerState
{
	// �ҋ@
	PLAYER_STATE_IDLE = 0,
	// ���ȏ���͂��Ȃ������ۂ̑ҋ@���[�V����
	PLAYER_STATE_IDLE_DANCE,
	// ����
	PLAYER_STATE_RUN,
	// �����ԊJ�n
	PLAYER_STATE_RUN_START,
	// �����Ԓ�~
	PLAYER_STATE_RUN_STOP,
	// �����Ԃ���U��Ԃ�
	PLAYER_STATE_RUN_TURN,
	// ���蒆�ǂɓ��������ۂ̋��ݏ��
	PLAYER_STATE_RUN_TO_FLINCH,
	// �W�����v���[�v
	PLAYER_STATE_JUMPLOOP, 
	// �W�����v�X�^�[�g
	PLAYER_STATE_JUMPSTART,
	// �W�����v�I������ҋ@��Ԃ֑J��
	PLAYER_STATE_JUMPEND_TO_IDLE,
	// �W�����v�I�����瑖���Ԃ֑J��
	PLAYER_STATE_JUMPEND_TO_RUN,
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
	PlayerObjectStateBase() {};

	/*
	@fn �f�X�g���N�^
	*/
	virtual ~PlayerObjectStateBase() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
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
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	virtual void Enter(PlayerObject* _owner, float _deltaTime) {};

protected:

	SkeletalMeshComponent* skeletalMeshComponent;
	PlayerState state;
	Vector3 velocity;
	float inputDeadSpace;
	const float MaxMoveSpeed = 1600.0f;

private:


};

