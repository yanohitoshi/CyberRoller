#pragma once
#include "ExplosionObjectStateBase.h"

class ExplosionObjectStateStartExplosion :
    public ExplosionObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	ExplosionObjectStateStartExplosion()
	: EmissiveColorBlue(Color::LightBlue)
	, EmissiveColorRed(Color::Red){};

	/*
	@fn �f�X�g���N�^
	*/
	~ExplosionObjectStateStartExplosion() {};

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
	
	/*
	@fn �_�ŏ���
	*/
	void Flashing();

	bool isHitJumpAttackPlayer;
	// ������ԕ����x�N�g��
	Vector3 blowAwayDirection;

	int explosionStart;

	int colorChangeTime;
	bool isRed;
	const Vector3 EmissiveColorRed; 
	const Vector3 EmissiveColorBlue;
};

