#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"

/*
@file TrackingEnemyStateTurn.h
@brief �ǐՂ���G�I�u�W�F�N�g�̃^�[����Ԃ��Ǘ�����N���X
*/
class EnemyObjectStateTurn :
    public EnemyObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	EnemyObjectStateTurn();

	/*
	@fn �f�X�g���N�^
	*/
	~EnemyObjectStateTurn()override;

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
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