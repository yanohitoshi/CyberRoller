#include "PlayerObjectStateRunStop.h"
#include "SkeletalMeshComponent.h"

PlayerObjectStateRunStop::PlayerObjectStateRunStop()
{
}

PlayerObjectStateRunStop::~PlayerObjectStateRunStop()
{
}

PlayerState PlayerObjectStateRunStop::Update(PlayerObject* _owner, float _deltaTime)
{
	//// positionに速度を足してキャラクターを動かす
	//_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	if (!skeletalMeshComponent->IsPlaying())
	{
		state = PlayerState::PLAYER_STATE_IDLE;
	}

	if (_owner->GetIsJumping() || _owner->GetJumpFlag() || _owner->GetSwitchJumpFlag())
	{
		state = PlayerState::PLAYER_STATE_JUMPSTART;
	}

	_owner->SetMoveSpeed(move);

	return state;
}

void PlayerObjectStateRunStop::Input(PlayerObject* _owner, const InputState& _keyState)
{

	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_X) == Pressed ||
		_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_Y) == Pressed)
	{
		//jumpFlag = true;
		_owner->SetJumpFlag(true);
		//isJumping = true;
		_owner->SetIsJumping(true);
	}

}

void PlayerObjectStateRunStop::Enter(PlayerObject* _owner, float _deltaTime)
{
	skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_RUN_STOP));
	state = PlayerState::PLAYER_STATE_RUN_STOP;
	move = _owner->GetMoveSpeed();
}
