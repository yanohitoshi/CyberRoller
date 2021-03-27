#include "PlayerObjectStateWalk.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateWalk::PlayerObjectStateWalk()
{
}

PlayerObjectStateWalk::~PlayerObjectStateWalk()
{
}

PlayerState PlayerObjectStateWalk::Update(PlayerObject* _owner, float _deltaTime)
{
	return state;
}

void PlayerObjectStateWalk::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateWalk::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_WALK));
	state = PlayerState::PLAYER_STATE_WALK;
}
