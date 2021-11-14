#pragma once
#include "EnemyObjectStateBase.h"

/*
@file TrackingEnemyStateIdle.h
@brief �ǐՂ���G�I�u�W�F�N�g�̃A�C�h�����O��Ԃ��Ǘ�����N���X
*/
class TrackingEnemyStateIdle :
    public EnemyObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	TrackingEnemyStateIdle();

	/*
	@fn �f�X�g���N�^
	*/
	~TrackingEnemyStateIdle()override;

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

	// �ҋ@����
	const int StayTime;
	// ���Ԃ��v��
	int frameCount;
};

