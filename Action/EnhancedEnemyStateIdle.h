#pragma once
#include "EnemyObjectStateBase.h"

class EnhancedEnemyStateIdle :
    public EnemyObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	EnhancedEnemyStateIdle();

	/*
	@fn �f�X�g���N�^
	*/
	~EnhancedEnemyStateIdle()override;

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

