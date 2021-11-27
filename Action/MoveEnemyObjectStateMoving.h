#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"

/*
@file MoveEnemyObjectStateMoving.h
@brief �ړ�����G�I�u�W�F�N�g�̈ړ���Ԃ��Ǘ�����N���X
*/
class MoveEnemyObjectStateMoving :
    public EnemyObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	MoveEnemyObjectStateMoving();

	/*
	@fn �f�X�g���N�^
	*/
	~MoveEnemyObjectStateMoving()override;

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

	/*
	@fn �ړ������֐�
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Move(EnemyObjectBase* _owner, float _deltaTime);

	// �ړ�����
	Vector3 moveDirection;
	// �ړ��Ԋu
	float moveDistance;
	// �����|�W�V����
	Vector3 firstPosition;

};