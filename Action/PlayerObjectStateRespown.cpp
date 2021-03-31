#include "PlayerObjectStateRespown.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateRespown::PlayerObjectStateRespown()
{
}

PlayerObjectStateRespown::~PlayerObjectStateRespown()
{
}

PlayerState PlayerObjectStateRespown::Update(PlayerObject* _owner, float _deltaTime)
{
	//// リスポーン演出入れてもいいかも

	_owner->SetRespawnFlag(false);
	_owner->SetIsAvailableInput(true);

	state = PlayerState::PLAYER_STATE_IDLE;

	return state;
}

void PlayerObjectStateRespown::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateRespown::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_IDLE));
	state = PlayerState::PLAYER_STATE_RESPAWN;
	velocity = _owner->GetVelocity();

}
