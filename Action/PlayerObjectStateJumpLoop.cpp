#include "PlayerObjectStateJumpLoop.h"

PlayerObjectStateJumpLoop::PlayerObjectStateJumpLoop(PlayerObject* _owner)
	: PlayerObjectStateBase(_owner)
{
}

PlayerObjectStateJumpLoop::~PlayerObjectStateJumpLoop()
{
}

PlayerState PlayerObjectStateJumpLoop::Update(PlayerObject* _owner, float _deltaTime)
{
	return PlayerState();
}

void PlayerObjectStateJumpLoop::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateJumpLoop::Enter(PlayerObject* _owner, float _deltaTime)
{
}
