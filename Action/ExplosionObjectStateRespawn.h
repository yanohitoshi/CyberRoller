#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateBase.h"

/*
@file ExplosionObjectStateRespawn.h
@brief ��������I�u�W�F�N�g�̃��X�|�[����Ԃ��Ǘ�����N���X
*/
class ExplosionObjectStateRespawn :
    public ExplosionObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	ExplosionObjectStateRespawn(){};

	/*
	@fn �f�X�g���N�^
	*/
	~ExplosionObjectStateRespawn() {};

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

	// ���X�|�[�����̃J�E���g�ϐ�
	int respawnCount;
	// �����|�W�V����
	Vector3 firstPosition;
};

