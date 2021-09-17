#pragma once
#include "EnemyObjectStateBase.h"

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

	void Move(EnemyObjectBase* _owner, float _deltaTime);
	Vector3 moveDirection;
	float moveDistance;
	Vector3 firstPosition;

};

