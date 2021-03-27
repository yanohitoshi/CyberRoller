#include "PlayerObjectStateDownOver.h"
#include "SkeletalMeshComponent.h"
PlayerObjectStateDownOver::PlayerObjectStateDownOver()
{
}

PlayerObjectStateDownOver::~PlayerObjectStateDownOver()
{
}

PlayerState PlayerObjectStateDownOver::Update(PlayerObject* _owner, float _deltaTime)
{
	return state;
}

void PlayerObjectStateDownOver::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateDownOver::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DOWN_OVER));
	state = PlayerState::PLAYER_STATE_DOWN_OVER;
}
