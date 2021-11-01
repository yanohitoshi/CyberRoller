#include "ExplosionObjectStateBase.h"

void ExplosionObjectStateBase::VerticalMove(ExplosionObject* _owner, float _deltaTime)
{
	++frameCount;
	if (frameCount % 30 == 0)
	{
		++angle;
		rate = Math::Cos(angle);
	}

	velocity.z = rate * VerticalMoveSpeed;

	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);
}
