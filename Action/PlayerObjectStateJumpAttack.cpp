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
	if (_owner->GetIsSelectingTargetEnemy())
	{
		Vector3 tmpPosition;
		tmpPosition = Vector3::Lerp(_owner->GetPosition(), attackTargetEnemy->GetPosition(), _deltaTime * 9.0);
		_owner->SetPosition(tmpPosition);
	}
	else
	{
		++unSelectTargetEnemyFrameCount;
		jumpAttackDirection.z = 0.0f;
		velocity = jumpAttackDirection * 3000.0f;
		// 重力にデルタタイムをかけた値を代入
		velocity.z -= PlayerObject::GetGravity() * _deltaTime;
		_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
	}

	if (_owner->GetIsJumpAttackSuccess() || unSelectTargetEnemyFrameCount > 15)
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
	// stateをジャンプ攻撃状態にして保存
	state = PlayerState::PLAYER_STATE_JUMP_ATTACK;
	unSelectTargetEnemyFrameCount = 0;
	_owner->SetIsAvailableJumpAttck(false);

	if (_owner->GetIsSelectingTargetEnemy())
	{
		attackTargetEnemy = _owner->GetAttackTargetEnemy();
	}
	else
	{
		jumpAttackDirection = _owner->GetCharaForwardVec();
	}
}
