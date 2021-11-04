#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObjectStateExplosionBlowAway :
    public PlayerObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateExplosionBlowAway();

	/*
	@fn �f�X�g���N�^
	*/
	~PlayerObjectStateExplosionBlowAway()override;

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	PlayerState Update(PlayerObject* _owner, float _deltaTime)override;

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Enter(PlayerObject* _owner, float _deltaTime)override;

private:

	// �q�b�g�����G�̃|�W�V����
	Vector3 hitEnemyPosition;
	// �m�b�N�o�b�N�������
	Vector3 knockBackDirection;
	// �m�b�N�o�b�N�̎��Ԃ𐔂���
	int knockBackFrameCount;
	float knockBackSpeed;
	// �m�b�N�o�b�N�̑��x�萔
	const float KnockBackPower;
	// �m�b�N�o�b�N���鎞�Ԓ萔
	const int KnockBackTime;
};

