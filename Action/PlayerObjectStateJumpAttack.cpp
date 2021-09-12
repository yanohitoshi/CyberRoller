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
	//// 移動速度にデルタタイムを掛けてそれをポジションに追加して更新
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
	//// ownerからownerのskeletalMeshComponentのポインタをもらう
	//skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	//// 再生するアニメーションをもらい再生をかける
	//skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMP_ATTACK));
	// stateをジャンプ攻撃状態にして保存
	state = PlayerState::PLAYER_STATE_JUMP_ATTACK;
	jumpAttackDirection = Vector3::Zero;
	attackTargetEnemy = _owner->GetAttackTargetEnemy();
}
