#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateIdlingDance.h
@brief �_���X��Ԃ��Ǘ�
*/
class PlayerObjectStateIdlingDance :
    public PlayerObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateIdlingDance();

	/*
	@fn �f�X�g���N�^
	*/
	~PlayerObjectStateIdlingDance()override;

	/*
	@fn �A�b�v�f�[�g
	@brief	state�ɉ����ăA�b�v�f�[�g���s��
	@param	_owner �e�N���X�̃|�C���^
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
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

	/*
	@fn isDancing��getter�֐�
	@return	static bool �_���X�����ǂ����̃t���O�ϐ�
	*/
	static bool GetIsDancing() { return isDancing; }

private:

	// �_���X��Ԃ��ǂ�����\���t���O�ϐ�
	static bool isDancing;
};

