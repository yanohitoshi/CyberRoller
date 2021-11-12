#pragma once
//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateJumpAttack.h
@brief �W�����v�U���J�n����W�����v�U���I����ԂɈڍs����܂ł��Ǘ�
*/
class PlayerObjectStateJumpAttack :
    public PlayerObjectStateBase
{
public:

	/*
	@fn �R���X�g���N�^
	*/
	PlayerObjectStateJumpAttack();

	/*
	@fn �f�X�g���N�^
	*/
	~PlayerObjectStateJumpAttack()override;

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
	// �^�[�Q�b�g�ƂȂ�G�𑨂��Ă��邩�ǂ���
	bool isSelectingTargetEnemy;
	// �^�[�Q�b�g�����Ȃ��ꍇ�̃W�����v�U���̃t���[�����J�E���g
	int unSelectTargetEnemyFrameCount;
	// �^�[�Q�b�g�����Ȃ��ꍇ�̃W�����v�U���̃X�s�[�h
	const float AttackSpeed;
	// �^�[�Q�b�g�����Ȃ��ꍇ�̃W�����v�U�����s������
	const int UnSelectTargetAttackTime;
	// �^�[�Q�b�g�����Ȃ��ꍇ�̃W�����v�U�����s������
	Vector3 jumpAttackDirection;

	// �^�[�Q�b�g�ƂȂ�G�̃|�C���^
	GameObject* attackTarget;

};

