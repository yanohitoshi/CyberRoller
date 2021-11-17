#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateBase.h"

/*
@file ExplosionObjectStateFall.h
@brief ������Ԃ��Ǘ�����N���X
*/
class ExplosionObjectStateFall :
    public ExplosionObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	ExplosionObjectStateFall()
		: FirstColorChangeTime(15) {};

	/*
	@fn �f�X�g���N�^
	*/
	~ExplosionObjectStateFall() {};

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	ExplosionObjectState Update(ExplosionObjectBase* _owner, float _deltaTime);

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Enter(ExplosionObjectBase* _owner, float _deltaTime);

private:

	/*
	@fn �_�ŏ���
	*/
	void Flashing();

	float fallSpeed;

	int fallCount;
	int colorChangeTime;
	bool isRed;
	//const float BlowAwaySpeed;
	const int FirstColorChangeTime;
};

