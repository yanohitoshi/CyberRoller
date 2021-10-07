#pragma once
#include "EnemyObjectStateBase.h"

class EnemyObjectStateAttack :
    public EnemyObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	EnemyObjectStateAttack();

	/*
	@fn �f�X�g���N�^
	*/
	~EnemyObjectStateAttack()override;

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

	// �ǐՑΏۂƂȂ�I�u�W�F�N�g��ۑ�����|�C���^�ϐ�
	GameObject* trackingObject;
	// �ǐ՗p�̉�]�x�N�g��
	Vector3 trackingRotationVec;
	// �����|�W�V����
	Vector3 firstPosition;
};

