#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitlePlayerObject.h"

// �N���X�̑O���錾
class TitlePlayerObject;
class SkeletalMeshComponent;
class MeshComponent;

/*
@enum�@TitlePlayerState
�^�C�g���ł̃v���C���[�̃X�e�[�^�X
*/
enum class TitlePlayerState
{
	RUN,
	JUMP_START,
	JUMP_LOOP,
	JUMP_ATTACK,
	STATE_NUM
};

/*
@file TitlePlayerStateBase.h
@brief �^�C�g���V�[�����ł̃v���C���[�̃X�e�[�^�X���Ǘ�����N���X�̊��N���X
*/
class TitlePlayerStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	TitlePlayerStateBase()
	: JumpLimitTime(13)
	, JumpSpeed(15.0f)
	, FirstJumpPower(40.0f)
	, Gravity(400.0f)
	, MaxFallSpeed(-200.0f){};

	/*
	@fn �f�X�g���N�^
	*/
	virtual ~TitlePlayerStateBase() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	virtual TitlePlayerState Update(TitlePlayerObject* _owner, float _deltaTime) = 0;

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	virtual void Enter(TitlePlayerObject* _owner, float _deltaTime) {};

protected:

	// �e�N���X�̃|�C���^���i�[���邽�߂�SkeletalMeshComponent�̃|�C���^�ϐ�
	SkeletalMeshComponent* skeletalMeshComponent;
	// �e�N���X�̃|�C���^���i�[���邽�߂�MeshComponent�̃|�C���^�ϐ�
	MeshComponent* meshComponent;
	// state�̑J�ڂ��s�����߂̕ϐ�
	TitlePlayerState state;
	Vector3 velocity;

	// �W�����v�𑱂���t���[���J�E���g�萔
	const float JumpLimitTime;
	const float JumpSpeed;
	const float FirstJumpPower;
	const float Gravity;
	const float MaxFallSpeed;
};

