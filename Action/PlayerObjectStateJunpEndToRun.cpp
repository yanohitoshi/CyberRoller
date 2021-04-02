#include "PlayerObjectStateJunpEndToRun.h"

PlayerObjectStateJunpEndToRun::PlayerObjectStateJunpEndToRun()
{
}

PlayerObjectStateJunpEndToRun::~PlayerObjectStateJunpEndToRun()
{
}

PlayerState PlayerObjectStateJunpEndToRun::Update(PlayerObject* _owner, float _deltaTime)
{
	return state;
}

void PlayerObjectStateJunpEndToRun::Input(PlayerObject* _owner, const InputState& _keyState)
{
}

void PlayerObjectStateJunpEndToRun::Enter(PlayerObject* _owner, float _deltaTime)
{
}
