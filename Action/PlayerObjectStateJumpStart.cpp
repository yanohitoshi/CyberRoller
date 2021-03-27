#include "PlayerObjectStateJumpStart.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateJumpStart::PlayerObjectStateJumpStart()
{
}

PlayerObjectStateJumpStart::~PlayerObjectStateJumpStart()
{
}

PlayerState PlayerObjectStateJumpStart::Update(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	
	if (!skeletalMeshComponent->IsPlaying())
	{
		state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}
	else if (skeletalMeshComponent->IsPlaying())
	{
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	return state;
}

void PlayerObjectStateJumpStart::Input(PlayerObject* _owner, const InputState& _keyState)
{

	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Released ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Released ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Released ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Released )
	{
		//isAvailableJumpKey = false;
		_owner->SetIsAvailableJumpKey(false);
		//isJumping = false;
		_owner->SetIsJumping(false);
		//jumpPower = FirstJumpPower;
		_owner->SetJumpPower(_owner->GetFirstJumpPower());
		//state = PlayerState::PLAYER_STATE_JUMPLOOP;
	}

}

void PlayerObjectStateJumpStart::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_JUMPSTART));
	state = PlayerState::PLAYER_STATE_JUMPSTART;
}
