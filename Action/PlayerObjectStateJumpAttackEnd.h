#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObjectStateJumpAttackEnd :
    public PlayerObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateJumpAttackEnd();

	/*
	@fn �f�X�g���N�^
	*/
	~PlayerObjectStateJumpAttackEnd()override;

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

	Vector3 jumpAttackDirection;
	GameObject* attackTargetEnemy;

	// �W�����v���s���Ă���t���[���𑪂�J�E���g�ϐ�
	int jumpFrameCount;
	// �W�����v���I���������ǂ����̃t���O�ϐ�
	bool endFlag;
	// �X�C�b�`�W�����v���̃W�����v�͂̉����x
	const float SuccessJumpAccelPower;
	// �X�C�b�`�W�����v���p�\�^�C��
	const int SuccessJumpTime;
};

