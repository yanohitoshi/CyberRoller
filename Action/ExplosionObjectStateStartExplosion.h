#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateBase.h"

/*
@file ExplosionObjectStateStartExplosion.h
@brief ��������I�u�W�F�N�g�̔����O�̗\��������Ǘ�����N���X
*/
class ExplosionObjectStateStartExplosion :
    public ExplosionObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	ExplosionObjectStateStartExplosion()
	: BlowAwaySpeed(1600.0f)
	, FirstColorChangeTime(15)
	, ExplosionStartTime(180){};

	/*
	@fn �f�X�g���N�^
	*/
	~ExplosionObjectStateStartExplosion() {};

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
	
	/*
	@fn �_�ŏ���
	*/
	void Flashing();

	// �W�����v�A�^�b�N�v���C���[�ɓ����������ǂ���
	bool isHitJumpAttackPlayer;
	// ������ԕ����x�N�g��
	Vector3 blowAwayDirection;

	// �����J�n���Ԃ��J�E���g
	int explosionStart;

	// �F��ύX���鎞��
	int colorChangeTime;
	// �Ԃ��ǂ���
	bool isRed;
	// ������ԃX�s�[�h�萔
	const float BlowAwaySpeed;
	//�ŏ��̐F�ύX���鎞��
	const int FirstColorChangeTime;

	// �����J�n����
	const int ExplosionStartTime;
};