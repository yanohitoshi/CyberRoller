#include "PlayerObjectStateJumpAttack.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateJumpAttack::PlayerObjectStateJumpAttack()
	: AttackSpeed(3000.0f)
	, UnSelectTargetAttackTime(15)
{
}

PlayerObjectStateJumpAttack::~PlayerObjectStateJumpAttack()
{
}

PlayerState PlayerObjectStateJumpAttack::Update(PlayerObject* _owner, float _deltaTime)
{
	// �^�[�Q�b�g�𑨂��Ă��Ă��^�[�Q�b�g��Active��������
	if (isSelectingTargetEnemy && attackTargetEnemy->GetState() == State::Active)
	{
		// ���|�W�V�����ϐ�
		Vector3 tmpPosition;
		// ���`�⊮���Ƃ�ϐ��ɕۑ�
		tmpPosition = Vector3::Lerp(_owner->GetPosition(), attackTargetEnemy->GetPosition(), _deltaTime * 9.0);
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

	// �U�������܂��̓W�����v�A�^�b�N�̎��Ԃ��I�����Ă�����X�e�[�^�X��ύX
	if (_owner->GetIsJumpAttackSuccess() || unSelectTargetEnemyFrameCount > UnSelectTargetAttackTime)
	{
		state = PlayerState::PLAYER_STATE_JUMP_ATTACK_END;
	}

	ChackDeadFlag(_owner);

	ChackTimeOverFlag();

	return state;
}

void PlayerObjectStateJumpAttack::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateJumpAttack::Enter(PlayerObject* _owner, float _deltaTime)
{
	// state���W�����v�U����Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_JUMP_ATTACK;
	unSelectTargetEnemyFrameCount = 0;

	// ��x�W�����v�U���g�p�s�ɃZ�b�g
	_owner->SetIsAvailableJumpAttck(false);

	isSelectingTargetEnemy = _owner->GetIsSelectingTargetEnemy();
	// �^�[�Q�b�g�𑨂��Ă��邩����
	if (isSelectingTargetEnemy)
	{
		attackTargetEnemy = _owner->GetAttackTargetEnemy();
	}
	else
	{
		jumpAttackDirection = _owner->GetCharaForwardVec();
	}
}
