#include "ExplosionObjectStateFall.h"
#include "MeshComponent.h"

ExplosionObjectState ExplosionObjectStateFall::Update(ExplosionObjectBase* _owner, float _deltaTime)
{
	++fallCount;

	velocity.z = -fallSpeed;

	_owner->SetPosition(_owner->GetPosition() + velocity * _deltaTime);

	Flashing();

	if (_owner->GetIsHitExplosionObject() || _owner->GetPosition().z < 0.0f)
	{
		state = ExplosionObjectState::EXPLOSION;
		return state;
	}

	return state;
}

void ExplosionObjectStateFall::Enter(ExplosionObjectBase* _owner, float _deltaTime)
{
	state = ExplosionObjectState::FALL;
	meshComponent = _owner->GetMeshComponent();
	// ‘¬“x‚ð‰Šú‰»
	velocity = Vector3::Zero;
	isRed = false;
	colorChangeTime = FirstColorChangeTime;
	fallCount = 0;
	angle = 0;
	_owner->SetState(State::Active);

	fallSpeed = _owner->GetFallSpeed();
}

void ExplosionObjectStateFall::Flashing()
{

	if (fallCount > 60)
	{
		colorChangeTime = 7;
	}

	if (fallCount > 120)
	{
		colorChangeTime = 3;
	}

	if (fallCount % colorChangeTime == 0)
	{
		if (isRed)
		{
			isRed = false;
		}
		else
		{
			isRed = true;
		}
	}

	if (isRed)
	{
		meshComponent->SetEmissiveColor(EmissiveColorRed);
	}
	else
	{
		meshComponent->SetEmissiveColor(EmissiveColorBlue);
	}
}
