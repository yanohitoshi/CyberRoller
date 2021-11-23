#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateBase.h"

/*
@file FallExplosionObjectStateIdle.h
@brief �������锚�����I�u�W�F�N�g�̃A�C�h�����O��Ԃ��Ǘ�����N���X
*/
class FallExplosionObjectStateIdle :
    public ExplosionObjectStateBase
{

public:

	/*
	@fn �R���X�g���N�^
	*/
	FallExplosionObjectStateIdle() 
		: StayTime(10) {};

	/*
	@fn �f�X�g���N�^
	*/
	~FallExplosionObjectStateIdle(){};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return ExplosionObjectState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	ExplosionObjectState Update(ExplosionObjectBase* _owner, float _deltaTime);

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Enter(ExplosionObjectBase* _owner, float _deltaTime);

private:

	// scale�l��ۑ�����ϐ�
	float nowScaleZ;
	// �ҋ@���Ԃ��v������J�E���g�ϐ�
	int stayCount;
	// �ҋ@���Ԓ萔
	const int StayTime;
};

