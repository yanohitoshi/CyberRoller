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
	if (isInput)
	{
		if (isContinue)
		{
			state = PlayerState::PLAYER_STATE_DOWN_UP;
		}
		else
		{
			state = PlayerState::PLAYER_STATE_DOWN_OVER;
		}
	}

	return state;
}

void PlayerObjectStateDownLoop::Input(PlayerObject* _owner, const InputState& _keyState)
{

	if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == Pressed ||
		_keyState.Keyboard.GetKeyDownValue(SDL_SCANCODE_C) == true)
	{
		isInput = true;
		isContinue = true;
	}
	else if (_keyState.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == Pressed ||
			 _keyState.Keyboard.GetKeyDownValue(SDL_SCANCODE_Z) == true)
	{
		isInput = true;
	}
	
}

void PlayerObjectStateDownLoop::Enter(PlayerObject* _owner, float _deltaTime)
{
	SkeletalMeshComponent* skeletalMeshComponent = _owner->GetSkeletalMeshComponent();
	skeletalMeshComponent->PlayAnimation(_owner->GetAnimation(PlayerState::PLAYER_STATE_DOWN_LOOP));
	state = PlayerState::PLAYER_STATE_DOWN_LOOP;
	isContinue = false;
	isInput = false;
}
