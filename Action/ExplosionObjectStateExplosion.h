#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateBase.h"

/*
@file ExplosionObjectStateExplosion.h
@brief ������Ԃ��Ǘ�����N���X
*/
class ExplosionObjectStateExplosion :
    public ExplosionObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	ExplosionObjectStateExplosion()
	: ExplosionTime(10){};

	/*
	@fn �f�X�g���N�^
	*/
	~ExplosionObjectStateExplosion() {};

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

	// �����̎��Ԃ��J�E���g����ϐ�
	int explosionCount;
	// ������������
	const int ExplosionTime;
};

