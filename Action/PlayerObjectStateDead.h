#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateDead.h
@brief ���S��Ԃ��Ǘ�
*/
class PlayerObjectStateDead :
    public PlayerObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateDead(PlayerObject* _owner);

	/*
	@fn �f�X�g���N�^
	*/
	~PlayerObjectStateDead()override;

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

	/*
	@fn ���A�J�ڃJ�E���g�����֐�
	@param	_owner �e�N���X�̃|�C���^
	*/
	void ToRespawnCountProcess(PlayerObject* _owner);

	// ���X�|�[����Ԃɓ���܂ł̃J�E���g�𑪂�ϐ�
	int respawnCount;

	// ���X�|�[����Ԃɓ��鎞��
	const int RespawnTime;
};

