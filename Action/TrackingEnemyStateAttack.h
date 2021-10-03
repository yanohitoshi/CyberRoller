#pragma once
#include "EnemyObjectStateBase.h"

/*
@file TrackingEnemyStateAttack.h
@brief �ǐՂ���G�I�u�W�F�N�g�̍U����Ԃ��Ǘ�����N���X
*/
class TrackingEnemyStateAttack :
    public EnemyObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	TrackingEnemyStateAttack();

	/*
	@fn �f�X�g���N�^
	*/
	~TrackingEnemyStateAttack()override;

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

	GameObject* trackingObject;
	Vector3 trackingRotationVec;
	Vector3 firstPosition;
};

