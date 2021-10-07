#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateRespown.h
@brief ���X�|�[����Ԃ��Ǘ�
*/
class PlayerObjectStateRespown :
    public PlayerObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateRespown();

	/*
	@fn �f�X�g���N�^
	*/
	~PlayerObjectStateRespown()override;

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

};

