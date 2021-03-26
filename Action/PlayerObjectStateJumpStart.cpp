#include "PlayerObjectStateJumpStart.h"

PlayerObjectStateJumpStart::PlayerObjectStateJumpStart(PlayerObject* _owner)
	: PlayerObjectStateBase(_owner)
{
}

PlayerObjectStateJumpStart::~PlayerObjectStateJumpStart()
{
}

PlayerState PlayerObjectStateJumpStart::Update(PlayerObject* _owner, float _deltaTime)
{
	return PlayerState();
}

void PlayerObjectStateJumpStart::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateJumpStart::Enter(PlayerObject* _owner, float _deltaTime)
{
}
