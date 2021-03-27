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
	return state;
}

void PlayerObjectStateDead::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateDead::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_PLAYER_DEAD));
	state = PlayerState::PLAYER_STATE_PLAYER_DEAD;
}
