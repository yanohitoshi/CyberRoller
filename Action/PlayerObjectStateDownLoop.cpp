#include "PlayerObjectStateDownLoop.h"
#include "SkeletalMeshComponent.h"
PlayerObjectStateDownLoop::PlayerObjectStateDownLoop()
{
}

PlayerObjectStateDownLoop::~PlayerObjectStateDownLoop()
{
}

PlayerState PlayerObjectStateDownLoop::Update(PlayerObject* _owner, float _deltaTime)
{
	return state;
}

void PlayerObjectStateDownLoop::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateDownLoop::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DOWN_LOOP));
	state = PlayerState::PLAYER_STATE_DOWN_LOOP;
}
