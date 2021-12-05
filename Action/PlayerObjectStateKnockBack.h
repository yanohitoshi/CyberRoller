#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateKnockBack.h
@brief �m�b�N�o�b�N�J�n����A�C�h�����O��ԂɈڍs����܂ł��Ǘ�
*/
class PlayerObjectStateKnockBack :
    public PlayerObjectStateBase
{
public:
	
	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateKnockBack(PlayerObject* _owner);

	/*
	@fn �f�X�g���N�^
	*/
	~PlayerObjectStateKnockBack()override;

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
	// �m�b�N�o�b�N�̑��x�萔
	const float KnockBackSpeed;
	// �m�b�N�o�b�N���鎞�Ԓ萔
	const int KnockBackTime;
};

