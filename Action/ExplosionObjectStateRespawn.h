#pragma once
#include "ExplosionObjectStateBase.h"

class ExplosionObjectStateRespawn :
    public ExplosionObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	ExplosionObjectStateRespawn()
		: MoveSpeed(50.0f) {};

	/*
	@fn �f�X�g���N�^
	*/
	~ExplosionObjectStateRespawn() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	ExplosionObjectState Update(ExplosionObject* _owner, float _deltaTime);

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Enter(ExplosionObject* _owner, float _deltaTime);

private:

	int frameCount;
	float rate;
	float angle;
	const float MoveSpeed;
};

