#include "PlayerObjectStateDead.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateDead::PlayerObjectStateDead()
{
}

PlayerObjectStateDead::~PlayerObjectStateDead()
{
}

PlayerState PlayerObjectStateDead::Update(PlayerObject* _owner, float _deltaTime)
{
	if (_owner->GetRespawnFlag() == false)
	{
		++reSpawnCount;
		if (reSpawnCount >= 120)
		{
			_owner->SetRespawnFlag(true);
			_owner->SetPosition(_owner->GetRespownPos());
			_owner->SetDeadFlag(false);
		}
	}
	if (_owner->GetRespawnFlag())
	{
		state = PlayerState::PLAYER_STATE_RESPAWN;
	}

	return state;
}

void PlayerObjectStateDead::Input(PlayerObject* _owner, const InputState& _keyState)
{

}

void PlayerObjectStateDead::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DEAD));
	state = PlayerState::PLAYER_STATE_DEAD;
	velocity = _owner->GetVelocity();
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	reSpawnCount = 0;
	_owner->SetIsAvailableInput(false);
}
