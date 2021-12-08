#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateIdle.h
@brief �A�C�h�����O��Ԃ��Ǘ�
*/
class PlayerObjectStateIdle :
    public PlayerObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateIdle();

	/*
	@fn �f�X�g���N�^
	*/
	~PlayerObjectStateIdle()override;

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	@return PlayerState�@�X�V�I�����̃X�e�[�^�X��Ԃ�
	*/
	PlayerState Update(PlayerObject* _owner, float _deltaTime)override;

	/*
	@fn �C���v�b�g
	@brief	state�ɉ����ē��͏������s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_keyState ���͏��
	*/
	void Input(PlayerObject* _owner, const InputState& _keyState)override;

	/*
	@fn state�ύX���̏�����
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void Enter(PlayerObject* _owner, float _deltaTime)override;

private:
	
	/*
	@fn ���̓`�F�b�N�����֐�
	@param	_owner �e�N���X�̃|�C���^
	*/
	void CheckMovableInputProcess(PlayerObject* _owner);

	/*
	@fn �_���X�J�n�J�E���g�֐�
	@brief	�_���X�J�n�܂ł̃J�E���g�𐔂����Ԃ�������t���O��؂�ւ���
	*/
	void DanceCountProcess();

	// �_���X��Ԃɐ؂�ւ���t���O�ϐ�
	bool isDanceFlag;
	// ���͂������ԃJ�E���g�𐔂���p�̃J�E���g�ϐ�
	int danceCount;
	// �_���X���J�n���鎞��
	const int DanceStartTime;
};