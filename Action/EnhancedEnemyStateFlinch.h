#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"

/*
@file EnhancedEnemyStateFlinch.h
@brief �����G�I�u�W�F�N�g�̋��ݏ�Ԃ��Ǘ�����N���X
*/
class EnhancedEnemyStateFlinch :
    public EnemyObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	EnhancedEnemyStateFlinch();

	/*
	@fn �f�X�g���N�^
	*/
	~EnhancedEnemyStateFlinch()override;

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

	// ���ݏ�Ԃ̎��Ԃ��J�E���g
	int flinchCount;
	// ������ԕ����x�N�g��
	Vector3 blowAwayDirection;

	// ���A���鎞�Ԓ萔
	const int EndTime;
	// ������ԗ͒萔
	const float BlowAwayPower;
	// ����������ї͒萔
	const float FirstBlowAwayPower;
	// �ő呬�x�萔
	const float MaxSpeed;
};