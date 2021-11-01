#include "ExplosionObjectStateIdle.h"

ExplosionObjectState ExplosionObjectStateIdle::Update(ExplosionObject* _owner, float _deltaTime)
{
	VerticalMove(_owner, _deltaTime);
	return state;
}

void ExplosionObjectStateIdle::Enter(ExplosionObject* _owner, float _deltaTime)
{
	state = ExplosionObjectState::IDLE;
	rate = 0.0f;
}
