#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObject.h"

// �N���X�̑O���錾
class PlayerObject;
class SkeletalMeshComponent;

/*
@enum�@PlayerState
�v���C���[�̃X�e�[�^�X���ʗp
*/
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
	PLAYER_STATE_KNOCKBACK,
	// �W�����v���[�v
	PLAYER_STATE_JUMPLOOP, 
	// �W�����v�X�^�[�g
	PLAYER_STATE_JUMPSTART,
	// �W�����v�I������ҋ@��Ԃ֑J��
	PLAYER_STATE_JUMPEND_TO_IDLE,
	// �W�����v�I�����瑖���Ԃ֑J��
	PLAYER_STATE_JUMPEND_TO_RUN,
	// �W�����v�U�����	
	PLAYER_STATE_JUMP_ATTACK,
	// �W�����v�U���I�����
	PLAYER_STATE_JUMP_ATTACK_END,
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
	// �������S���
	PLAYER_STATE_FALL_DEAD,
	// ���X�|�[�����
	PLAYER_STATE_RESPAWN,

	// ���A�j���[�V������
	PLAYER_STATE_NUM,
};

/*
@file PlayerObjectStateBase.h
@brief �v���C���[�̃X�e�[�g�p�^�[���̊��N���X
*/
class PlayerObjectStateBase
{
public:
	
	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateBase()
		: MaxFallSpeed(-2000.0f)
		, MaxMoveSpeed(1800.0f)
	{};

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

	/*
	@fn �n�ʈړ������֐�
	@param	_owner �e�N���X�̃|�C���^
	@param	_keyState ���͏��
	*/
	void GroundMove(PlayerObject* _owner, const InputState& _keyState);

	/*
	@fn ���̓`�F�b�N�����֐�
	@param	_owner �e�N���X�̃|�C���^
	@param	_keyState ���͏��
	*/
	void CheckInput(PlayerObject* _owner, const InputState& _keyState);
	
	/*
	@fn ���S��Ԃ��m�F����֐�
	@param	_owner �e�N���X�̃|�C���^
	*/
	void CheckDeadFlag(PlayerObject* _owner);

	/*
	@fn �^�C���I�[�o�[���m�F����֐�
	*/
	void CheckTimeOverFlag();

	/*
	@fn ��]�����֐�
	@param	_owner �e�N���X�̃|�C���^
	@param	_forward ��]����������x�N�g��
	@param	_tmpForward ��]������O�̕����x�N�g��
	*/
	void RotationProcess(PlayerObject* _owner,Vector3 _forward,Vector3 _tmpForward);

	/*
	@fn �A�i���O�X�e�B�b�N�����֐�
	@param	_keyState ���͏��
	*/
	Vector3 CheckControllerAxis(const InputState& _keyState);

protected:
	
	/*
	@fn �W�����v�n�̃X�e�[�^�X�̎����͂�����ꍇ�̏����֐�
	@param	_owner �e�N���X�̃|�C���^
	@param	_axis �␳�ς݂̃A�i���O�X�e�B�b�N���
	*/
	void InputJumpMovableProcess(PlayerObject* _owner, Vector3 _axis);

	// �e�N���X�̃|�C���^���i�[���邽�߂�SkeletalMeshComponent�̃|�C���^�ϐ�
	SkeletalMeshComponent* skeletalMeshComponent;
	// state�̑J�ڂ��s�����߂̕ϐ�
	PlayerState state;
	// ���x���|�W�V�����ɍ�p���鑬�x���i�[���邽�߂�Vector3�ϐ�
	Vector3 velocity;
	// ���x���i�[���邽�߂̕ϐ�
	float moveSpeed;
	// ���͐����̒l���i�[���邽�߂̕ϐ�
	float inputDeadSpace;
	// �ړ����x�̍ō��l
	const float MaxMoveSpeed;
	// �ő嗎�����x�̋K��l
	const float MaxFallSpeed;

private:

	/*
	@fn ���̓`�F�b�N�֐������֐�
	@param	_owner �e�N���X�̃|�C���^
	@param	_keyState ���͏��
	*/
	void CheckInputProcess(PlayerObject* _owner, const InputState& _keyState);

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
};

