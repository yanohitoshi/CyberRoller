#include "PlayerObjectStateRunStart.h"

PlayerObjectStateRunStart::PlayerObjectStateRunStart()
{
}

PlayerObjectStateRunStart::~PlayerObjectStateRunStart()
{
}

PlayerState PlayerObjectStateRunStart::Update(PlayerObject* _owner, float _deltaTime)
{
	return state;
}

void PlayerObjectStateRunStart::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateRunStart::Enter(PlayerObject* _owner, float _deltaTime)
{
}
