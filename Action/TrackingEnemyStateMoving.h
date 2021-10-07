#pragma once
#include "EnemyObjectStateBase.h"

// ���݂�statePattern�̎d�l��̃N���X��ǉ����Ȃ��Ƃ����Ȃ��ꍇ�����肻�̂��߂̋�̃N���X�ł��B
// ���P���@�͍����ł��B

/*
@file TrackingEnemyStateMoving.h
@brief �ǐՂ���G�I�u�W�F�N�g�̈ړ���Ԃ��Ǘ�����N���X
*/
class TrackingEnemyStateMoving :
    public EnemyObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	TrackingEnemyStateMoving();

	/*
	@fn �f�X�g���N�^
	*/
	~TrackingEnemyStateMoving()override;

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

