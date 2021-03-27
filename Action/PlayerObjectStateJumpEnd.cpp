#include "PlayerObjectStateJumpEnd.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateJumpEnd::PlayerObjectStateJumpEnd()
{
}

PlayerObjectStateJumpEnd::~PlayerObjectStateJumpEnd()
{
}

PlayerState PlayerObjectStateJumpEnd::Update(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	if (!skeletalMeshComponent->IsPlaying())
	{
		state = PlayerState::PLAYER_STATE_IDLE;
	}

	return state;
}

void PlayerObjectStateJumpEnd::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateJumpEnd::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPEND));
	state = PlayerState::PLAYER_STATE_JUMPEND;
}
