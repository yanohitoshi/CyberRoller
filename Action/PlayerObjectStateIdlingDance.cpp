#include "PlayerObjectStateIdlingDance.h"

PlayerObjectStateIdlingDance::PlayerObjectStateIdlingDance()
{
}

PlayerObjectStateIdlingDance::~PlayerObjectStateIdlingDance()
{
}

PlayerState PlayerObjectStateIdlingDance::Update(PlayerObject* _owner, float _deltaTime)
{
	return state;
}

void PlayerObjectStateIdlingDance::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateIdlingDance::Enter(PlayerObject* _owner, float _deltaTime)
{
}
