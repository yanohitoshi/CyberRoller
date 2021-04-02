#include "PlayerObjectStateRunStop.h"

PlayerObjectStateRunStop::PlayerObjectStateRunStop()
{
}

PlayerObjectStateRunStop::~PlayerObjectStateRunStop()
{
}

PlayerState PlayerObjectStateRunStop::Update(PlayerObject* _owner, float _deltaTime)
{
	return state;
}

void PlayerObjectStateRunStop::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateRunStop::Enter(PlayerObject* _owner, float _deltaTime)
{
}
