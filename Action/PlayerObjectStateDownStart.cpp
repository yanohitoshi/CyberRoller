#include "PlayerObjectStateDownStart.h"
#include "SkeletalMeshComponent.h"
PlayerObjectStateDownStart::PlayerObjectStateDownStart()
{
}

PlayerObjectStateDownStart::~PlayerObjectStateDownStart()
{
}

PlayerState PlayerObjectStateDownStart::Update(PlayerObject* _owner, float _deltaTime)
{
	return state;
}

void PlayerObjectStateDownStart::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateDownStart::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DOWN));
	state = PlayerState::PLAYER_STATE_DOWN;
}
