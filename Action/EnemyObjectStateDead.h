#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"

/*
@file EnemyObjectStateDead.h
@brief �G�I�u�W�F�N�g�̎��S��Ԃ��Ǘ�����N���X
*/
class EnemyObjectStateDead :
    public EnemyObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	EnemyObjectStateDead(EnemyObjectBase* _owner);

	/*
	@fn �f�X�g���N�^
	*/
	~EnemyObjectStateDead()override;

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

	// player�̃|�C���^��ۑ�����|�C���^�ϐ�
	GameObject* playerObject;
	// ������ԕ����x�N�g��
	Vector3 blowAwayDirection;

	// ���S��Ԃ̎��Ԃ��J�E���g
	int frameCount;
	// ���X�|�[�����鎞�Ԓ萔
	const int RespawnTime;
	// �`����I�t�ɂ��鎞�Ԓ萔
	const int InvisibleTime;
	// ������ї�
	const float BlowAwayPower;
	// ������я���
	const float FirstBlowAwayPower;
	// �ő呬�x
	const float MaxSpeed;
};