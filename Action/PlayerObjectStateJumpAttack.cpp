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
	// state‚ğƒWƒƒƒ“ƒvUŒ‚ó‘Ô‚É‚µ‚Ä•Û‘¶
	state = PlayerState::PLAYER_STATE_JUMP_ATTACK;
	jumpAttackDirection = Vector3::Zero;
	attackTargetEnemy = _owner->GetAttackTargetEnemy();
}
