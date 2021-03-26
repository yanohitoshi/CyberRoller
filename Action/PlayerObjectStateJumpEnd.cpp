#include "PlayerObjectStateJumpEnd.h"

PlayerObjectStateJumpEnd::PlayerObjectStateJumpEnd(PlayerObject* _owner)
	: PlayerObjectStateBase(_owner)
{
}

PlayerObjectStateJumpEnd::~PlayerObjectStateJumpEnd()
{
}

PlayerState PlayerObjectStateJumpEnd::Update(PlayerObject* _owner, float _deltaTime)
{
	return PlayerState();
}

void PlayerObjectStateJumpEnd::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateJumpEnd::Enter(PlayerObject* _owner, float _deltaTime)
{
}
