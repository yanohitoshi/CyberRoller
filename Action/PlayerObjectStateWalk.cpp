#include "PlayerObjectStateWalk.h"

PlayerObjectStateWalk::PlayerObjectStateWalk(PlayerObject* _owner)
	: PlayerObjectStateBase(_owner)
{
}

PlayerObjectStateWalk::~PlayerObjectStateWalk()
{
}

PlayerState PlayerObjectStateWalk::Update(PlayerObject* _owner, float _deltaTime)
{
	return PlayerState();
}

void PlayerObjectStateWalk::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateWalk::Enter(PlayerObject* _owner, float _deltaTime)
{
}
