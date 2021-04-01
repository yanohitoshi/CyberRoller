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
	if (!skeletalMeshComponent->IsPlaying())
	{
		state = PlayerState::PLAYER_STATE_DOWN_LOOP;
	}

	return state;
}

void PlayerObjectStateDownStart::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateDownStart::Enter(PlayerObject* _owner, float _deltaTime)
{
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DOWNSTART));
	state = PlayerState::PLAYER_STATE_DOWNSTART;
}
