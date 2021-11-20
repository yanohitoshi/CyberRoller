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
	FallExplosionObjectStateRespawn() {};

	/*
	@fn �f�X�g���N�^
	*/
	~FallExplosionObjectStateRespawn() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	ExplosionObjectState Update(ExplosionObjectBase* _owner, float _deltaTime);

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Enter(ExplosionObjectBase* _owner, float _deltaTime);

private:

	void SetRandPosition(ExplosionObjectBase* _owner);
	void SetRandFallSpeed(ExplosionObjectBase* _owner);

	// ���X�|�[�����̃J�E���g�ϐ�
	int respawnCount;
	Vector3 firstPosition;
};
