#pragma once
#include "EnemyObjectStateBase.h"

/*
@file TrackingEnemyStateReposition.h
@brief �ǐՂ���G�I�u�W�F�N�g�̒ǐՏꏊ���猳�̈ʒu�ɖ߂�܂ł��Ǘ�����N���X
*/
class TrackingEnemyStateReposition :
    public EnemyObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	TrackingEnemyStateReposition();

	/*
	@fn �f�X�g���N�^
	*/
	~TrackingEnemyStateReposition()override;

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

	Vector3 firstPosition;
	Vector3 repositionRotationVec;
};

