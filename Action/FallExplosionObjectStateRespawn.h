#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateBase.h"

/*
@file FallExplosionObjectStateRespawn.h
@brief �������锚�����I�u�W�F�N�g�̃��X�|�[�����Ǘ�����N���X
*/
class FallExplosionObjectStateRespawn :
    public ExplosionObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	FallExplosionObjectStateRespawn()
	: MaxFallSpeed(1000.0f)
	, LowestFallSpeed(300.0f){};

	/*
	@fn �f�X�g���N�^
	*/
	~FallExplosionObjectStateRespawn() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return ExplosionObjectState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	ExplosionObjectState Update(ExplosionObjectBase* _owner, float _deltaTime);

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Enter(ExplosionObjectBase* _owner, float _deltaTime);

private:

	/*
	@fn �����_���ȃ|�W�V�������Z�b�g
	@param	_owner �e�N���X�̃|�C���^
	*/
	void SetRandPosition(ExplosionObjectBase* _owner);

	/*
	@fn �����_���ȗ������x���Z�b�g
	@param	_owner �e�N���X�̃|�C���^
	*/
	void SetRandFallSpeed(ExplosionObjectBase* _owner);

	// ���X�|�[�����̃J�E���g�ϐ�
	int respawnCount;
	// �����|�W�V����
	Vector3 firstPosition;

	// �ő嗎�����x
	const float MaxFallSpeed;
	// �������x�̍Œ�l
	const float LowestFallSpeed;
};

