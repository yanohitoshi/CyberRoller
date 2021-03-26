#include "PlayerObjectStateOver.h"

PlayerObjectStateOver::PlayerObjectStateOver(PlayerObject* _owner)
	: PlayerObjectStateBase(_owner)
{
}

PlayerObjectStateOver::~PlayerObjectStateOver()
{
}

PlayerState PlayerObjectStateOver::Update(PlayerObject* _owner, float _deltaTime)
{
	return PlayerState();
}

void PlayerObjectStateOver::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateOver::Enter(PlayerObject* _owner, float _deltaTime)
{
}
