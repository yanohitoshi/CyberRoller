#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

// �N���X�̑O���錾
class SkeletalMeshComponent;

/*
@file PlayerObjectStateRunStop.h
@brief ���肩���~���Ǘ�
*/
class PlayerObjectStateRunStop :
    public PlayerObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateRunStop();

	/*
	@fn �f�X�g���N�^
	*/
	~PlayerObjectStateRunStop()override;

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

private:

	// �U��Ԃ�ɓ���邩�ǂ����̐����J�E���g
	int isTurnCount;
	// ������
	float decelerationForce;
	// �O��̍s��ꂽ�^�[������Ԋu���󂯂邽�߂̋K��l
	const int TurnDelayValue;
	// �^�[���ɓ����J�E���g�̋K��l
	const int TurnValue;
};

