#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"

/*
@file EnemyObjectStateRespawn.h
@brief �G�I�u�W�F�N�g�̃��X�|�[����Ԃ��Ǘ�����N���X
*/
class EnemyObjectStateRespawn :
    public EnemyObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	EnemyObjectStateRespawn();

	/*
	@fn �f�X�g���N�^
	*/
	~EnemyObjectStateRespawn()override;

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
	// ���X�|�[�����̈ړ����x
	const float RespawnMoveSpeed;
	// �ړ�����
	Vector3 moveDirection;
	// ���̃|�W�V����
	Vector3 nowPosition;
};

