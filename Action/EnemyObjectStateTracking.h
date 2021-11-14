#pragma once
#include "EnemyObjectStateBase.h"

/*
@file TrackingEnemyStateTracking.h
@brief �ǐՂ���G�I�u�W�F�N�g�̒ǐՏ�Ԃ��Ǘ�����N���X
*/
class EnemyObjectStateTracking :
    public EnemyObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	EnemyObjectStateTracking();

	/*
	@fn �f�X�g���N�^
	*/
	~EnemyObjectStateTracking()override;

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

	// �ǐՂ���I�u�W�F�N�g�̃|�C���^
	GameObject* trackingObject;
	// �ǐՕ����̃x�N�g����
	Vector3 trackingRotationVec;
	// �����|�W�V����
	Vector3 firstPosition;
	// �ǐՂłǂ��܂ŋ߂Â����̒l
	const float TrackingLengthValue;
};

