#include "PlayerObjectStateDead.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateDead::PlayerObjectStateDead()
	: respawnTime(120)
{
}

PlayerObjectStateDead::~PlayerObjectStateDead()
{
}

PlayerState PlayerObjectStateDead::Update(PlayerObject* _owner, float _deltaTime)
{
	if (_owner->GetRespawnFlag() == false)
	{
		++respawnCount;
		if (respawnCount >= respawnTime)
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

	// XV‚³‚ê‚½state‚ð•Ô‚·
	return state;
}

void PlayerObjectStateDead::Input(PlayerObject* _owner, const InputState& _keyState)
{

}

void PlayerObjectStateDead::Enter(PlayerObject* _owner, float _deltaTime)
{
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DEAD));
	state = PlayerState::PLAYER_STATE_DEAD;
	velocity = _owner->GetVelocity();
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	respawnCount = 0;
	_owner->SetIsAvailableInput(false);
}
