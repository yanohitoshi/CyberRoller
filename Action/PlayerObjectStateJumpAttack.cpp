#include "PlayerObjectStateJumpAttack.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateJumpAttack::PlayerObjectStateJumpAttack()
{
}

PlayerObjectStateJumpAttack::~PlayerObjectStateJumpAttack()
{
}

PlayerState PlayerObjectStateJumpAttack::Update(PlayerObject* _owner, float _deltaTime)
{
	//jumpAttackDirection = attackTargetEnemy->GetPosition() - _owner->GetPosition();
	//jumpAttackDirection.Normalize();
	//velocity = jumpAttackDirection * 1000.0f;
	//// �ړ����x�Ƀf���^�^�C�����|���Ă�����|�W�V�����ɒǉ����čX�V
	//_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
	Vector3 tmpPosition;
	tmpPosition = Vector3::Lerp(_owner->GetPosition(), attackTargetEnemy->GetPosition(), _deltaTime * 9.0);
	_owner->SetPosition(tmpPosition);

	if (_owner->GetIsJumpAttackSuccess())
	{
		state = PlayerState::PLAYER_STATE_JUMP_ATTACK_END;
	}

	return state;
}

void PlayerObjectStateJumpAttack::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateJumpAttack::Enter(PlayerObject* _owner, float _deltaTime)
{
	//// owner����owner��skeletalMeshComponent�̃|�C���^�����炤
	//skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	//// �Đ�����A�j���[�V���������炢�Đ���������
	//skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMP_ATTACK));
	// state���W�����v�U����Ԃɂ��ĕۑ�
	state = PlayerState::PLAYER_STATE_JUMP_ATTACK;
	jumpAttackDirection = Vector3::Zero;
	attackTargetEnemy = _owner->GetAttackTargetEnemy();
}
