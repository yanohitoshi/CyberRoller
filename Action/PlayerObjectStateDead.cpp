#include "PlayerObjectStateDead.h"

PlayerObjectStateDead::PlayerObjectStateDead(PlayerObject* _owner)
	: PlayerObjectStateBase(_owner)
{
}

PlayerObjectStateDead::~PlayerObjectStateDead()
{
}

PlayerState PlayerObjectStateDead::Update(PlayerObject* _owner, float _deltaTime)
{
	return PlayerState();
}

void PlayerObjectStateDead::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateDead::Enter(PlayerObject* _owner, float _deltaTime)
{
}
