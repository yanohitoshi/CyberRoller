#include "ExplosionObjectStateIdle.h"

ExplosionObjectState ExplosionObjectStateIdle::Update(ExplosionObject* _owner, float _deltaTime)
{

	VerticalMove(_owner, _deltaTime);

	if (nowScaleZ > 0.5f)
	{
		nowScaleZ -= 0.5f;
		_owner->SetScaleZ(nowScaleZ);
	}

	return state;
}

void ExplosionObjectStateIdle::Enter(ExplosionObject* _owner, float _deltaTime)
{
	state = ExplosionObjectState::IDLE;
	rate = 0.0f;
	nowScaleZ = _owner->GetScaleVec().z;
}
