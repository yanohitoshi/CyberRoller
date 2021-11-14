//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PlayerObjectStateJumpAttack.h"
#include "SkeletalMeshComponent.h"

/*
@fn �R���X�g���N�^
*/
PlayerObjectStateJumpAttack::PlayerObjectStateJumpAttack()
	: AttackSpeed(3000.0f)
	, UnSelectTargetAttackTime(15)
{
}

/*
@fn �f�X�g���N�^
*/
PlayerObjectStateJumpAttack::~PlayerObjectStateJumpAttack()
{
}

/*
@fn �A�b�v�f�[�g
@brief	state�ɉ����ăA�b�v�f�[�g���s��
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
PlayerState PlayerObjectStateJumpAttack::Update(PlayerObject* _owner, float _deltaTime)
{
	// �^�[�Q�b�g�𑨂��Ă��Ă��^�[�Q�b�g��Active��������
	if (isSelectingTargetEnemy && attackTarget->GetState() == State::Active)
	{
		// ���|�W�V�����ϐ�
		Vector3 tmpPosition;
		// ���`�⊮���Ƃ�ϐ��ɕۑ�
		tmpPosition = Vector3::Lerp(_owner->GetPosition(), attackTarget->GetPosition(), _deltaTime * 9.0);
		// �|�W�V�������Z�b�g
		_owner->SetPosition(tmpPosition);
	}
	else // �^�[�Q�b�g�����Ȃ��ꍇ�̃W�����v�A�^�b�N�ړ�����
	{
		++unSelectTargetEnemyFrameCount;
		jumpAttackDirection.z = 0.0f;
		velocity = jumpAttackDirection * AttackSpeed;
		_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
	} 


	// �W�����v�A�^�b�N�����܂��̓W�����v�A�^�b�N�̎��Ԃ��I�����Ă�����X�e�[�^�X��ύX
	if (_owner->GetIsJumpAttackSuccess() || unSelectTargetEnemyFrameCount > UnSelectTargetAttackTime)
	{
		_owner->SetMoveSpeed(AttackSpeed);
		state = PlayerState::PLAYER_STATE_JUMP_ATTACK_END;
	}

	CheckDeadFlag(_owner);

	CheckTimeOverFlag();

	return state;
}

/*
@fn state�ύX���̏�����
@param	_owner �e�N���X�̃|�C���^
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void PlayerObjectStateJumpAttack::Enter(PlayerObject* _owner, float _deltaTime)
{
	// state���W�����v�U����Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_JUMP_ATTACK;
	unSelectTargetEnemyFrameCount = 0;

	// ��x�W�����v�U���g�p�s�ɃZ�b�g
	_owner->SetIsAvailableJumpAttck(false);

	isSelectingTargetEnemy = _owner->GetIsSelectingTargetObject();
	// �^�[�Q�b�g�𑨂��Ă��邩����
	if (isSelectingTargetEnemy && _owner->GetAttackTargetEnemy()->GetState() == State::Active)
	{
		attackTarget = _owner->GetAttackTargetEnemy();
	}
	else
	{
		jumpAttackDirection = _owner->GetCharaForwardVec();
	}
}
