#pragma once
#include "EnemyObjectStateBase.h"

/*
@file EnemyObjectStateTracking.h
@brief �G�I�u�W�F�N�g�̒ǐՏ�Ԃ��Ǘ�����N���X
*/
class EnemyObjectStateTracking :
    public EnemyObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	EnemyObjectStateTracking(EnemyObjectBase* _owner);

	/*
	@fn �f�X�g���N�^
	*/
	~EnemyObjectStateTracking()override;

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

	/*
	@brief	�ǐՒ��̈ړ�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void TrackingMove(EnemyObjectBase* _owner, float _deltaTime);

	// �ǐՕ����̃x�N�g����
	Vector3 trackingRotationVec;
	// �����|�W�V����
	Vector3 firstPosition;
	// �ǐՂłǂ��܂ŋ߂Â����̒l
	const float TrackingLengthValue;
};