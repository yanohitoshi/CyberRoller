#pragma once
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateFallDead.h
@brief �������S��Ԃ��Ǘ�
*/
class PlayerObjectStateFallDead :
    public PlayerObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateFallDead();

	/*
	@fn �f�X�g���N�^
	*/
	~PlayerObjectStateFallDead()override;

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
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