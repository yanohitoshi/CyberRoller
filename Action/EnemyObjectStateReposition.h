#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"

/*
@file EnemyObjectStateReposition.h
@brief �G�I�u�W�F�N�g�̒ǐՏꏊ���猳�̈ʒu�ɖ߂�܂ł��Ǘ�����N���X
*/
class EnemyObjectStateReposition :
    public EnemyObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	EnemyObjectStateReposition();

	/*
	@fn �f�X�g���N�^
	*/
	~EnemyObjectStateReposition()override;

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
	//�����|�W�V����
	Vector3 firstPosition;
	// ���̃|�W�V�����ɖ߂�ۂ̕���
	Vector3 repositionRotationVec;
	// �A�C�h�����O�ֈڍs����K��l
	const float IdlingLength;
};