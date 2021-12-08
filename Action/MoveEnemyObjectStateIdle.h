#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"

/*
@file MoveEnemyObjectStateIdle.h
@brief �ړ�����G�I�u�W�F�N�g�̃A�C�h�����O��Ԃ��Ǘ�����N���X
*/
class MoveEnemyObjectStateIdle :
    public EnemyObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	MoveEnemyObjectStateIdle();

	/*
	@fn �f�X�g���N�^
	*/
	~MoveEnemyObjectStateIdle()override;

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return EnemyState ���̃X�e�[�^�X
	*/
	EnemyState Update(EnemyObjectBase* _owner, float _deltaTime)override;

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Enter(EnemyObjectBase* _owner, float _deltaTime)override;

private:

};