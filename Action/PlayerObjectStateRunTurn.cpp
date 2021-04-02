#include "PlayerObjectStateRunTurn.h"

PlayerObjectStateRunTurn::PlayerObjectStateRunTurn()
{
}

PlayerObjectStateRunTurn::~PlayerObjectStateRunTurn()
{
}

PlayerState PlayerObjectStateRunTurn::Update(PlayerObject* _owner, float _deltaTime)
{
	return state;
}

void PlayerObjectStateRunTurn::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateRunTurn::Enter(PlayerObject* _owner, float _deltaTime)
{
}
