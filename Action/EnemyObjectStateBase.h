#pragma once

#include "EnemyObjectBase.h"

// �N���X�̑O���錾
class EnemyObjectBase;
class SkeletalMeshComponent;

/*
@enum�@PlayerState
�v���C���[�̃X�e�[�^�X���ʗp
*/
enum class EnemyState
{
	// �ҋ@
	ENEMY_STATE_IDLE = 0,
	// ����
	ENEMY_STATE_RUN,
	// �����Ԃ���U��Ԃ�
	ENEMY_STATE_RUN_TURN,

	// ���A�j���[�V������
	ENEMY_STATE_NUM,
};

class EnemyObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	EnemyObjectStateBase()
		: MaxFallSpeed(-2000.0f)
		, MaxMoveSpeed(1600.0f)
	{};

	/*
	@fn �f�X�g���N�^
	*/
	virtual ~EnemyObjectStateBase() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	virtual EnemyState Update(EnemyObjectBase* _owner, float _deltaTime) = 0;

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	virtual void Enter(EnemyObjectBase* _owner, float _deltaTime) {};

	///*
	//@fn �n�ʈړ������֐�
	//@param	_owner �e�N���X�̃|�C���^
	//@param	_keyState ���͏��
	//*/
	//void GroundMove(EnemyObject* _owner, const InputState& _keyState);

	///*
	//@fn ��]�����֐�
	//@param	_owner �e�N���X�̃|�C���^
	//@param	_keyState ���͏��
	//*/
	//void RotationProcess(EnemyObject* _owner, Vector3 _forward, Vector3 _tmpForward);

protected:

	// �e�N���X�̃|�C���^���i�[���邽�߂�SkeletalMeshComponent�̃|�C���^�ϐ�
	SkeletalMeshComponent* skeletalMeshComponent;
	// state�̑J�ڂ��s�����߂̕ϐ�
	EnemyState state;
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


};
