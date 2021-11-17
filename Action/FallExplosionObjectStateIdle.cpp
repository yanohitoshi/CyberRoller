#include "FallExplosionObjectStateIdle.h"

ExplosionObjectState FallExplosionObjectStateIdle::Update(ExplosionObjectBase* _owner, float _deltaTime)
{
	if (nowScaleZ > 0.5f)
	{
		nowScaleZ -= 0.5f;
		_owner->SetScaleZ(nowScaleZ);
	}
	else
	{
		_owner->SetState(State::Active);
	}

	if (!_owner->GetIsFallStart())
	{
		return state;
	}

	++stayCount;

	if (stayCount >= StayTime && _owner->GetIsFallStart())
	{
		state = ExplosionObjectState::FALL;
	}


	return state;
}

void FallExplosionObjectStateIdle::Enter(ExplosionObjectBase* _owner, float _deltaTime)
{
	state = ExplosionObjectState::IDLE;
	rate = 0.0f;
	angle = 0.0f;
	nowScaleZ = _owner->GetScaleVec().z;

	stayCount = 0;
}
