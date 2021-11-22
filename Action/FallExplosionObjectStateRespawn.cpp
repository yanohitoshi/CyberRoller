#include "FallExplosionObjectStateRespawn.h"
#include "MeshComponent.h"

ExplosionObjectState FallExplosionObjectStateRespawn::Update(ExplosionObjectBase* _owner, float _deltaTime)
{
	++respawnCount;

	if (respawnCount > 240)
	{
		_owner->SetIsHitExplosionObject(false);
		meshComponent->SetVisible(true);
		meshComponent->SetEmissiveColor(EmissiveColorBlue);
		_owner->SetRotation(Quaternion::Identity);
		_owner->SetScaleZ(5.0f);
		state = ExplosionObjectState::IDLE;
	}

	return state;
}

void FallExplosionObjectStateRespawn::Enter(ExplosionObjectBase* _owner, float _deltaTime)
{
	state = ExplosionObjectState::RESPAWN;
	firstPosition = _owner->GetFirstPosition();
	respawnCount = 0;
	meshComponent = _owner->GetMeshComponent();
	_owner->SetIsExplode(false);
	_owner->SetState(State::Disabling);

	SetRandPosition(_owner);
	SetRandFallSpeed(_owner);
}

void FallExplosionObjectStateRespawn::SetRandPosition(ExplosionObjectBase* _owner)
{
	Vector3 fallArea = Vector3::Zero;

	fallArea = _owner->GetFallArea();
	float randValueX = (float)(rand() % (int)(fallArea.x / 2.0f));
	float randValueY = (float)(rand() % (int)(fallArea.y / 2.0f));

	int plus_minus_value = rand() % 4;

	Vector3 tmpPosition = firstPosition;

	switch (plus_minus_value)
	{
	case(0):
		tmpPosition.x += randValueX;
		tmpPosition.y += randValueY;
		break;
	case(1):
		tmpPosition.x += randValueX;
		tmpPosition.y -= randValueY;
		break;
	case(2):
		tmpPosition.x -= randValueX;
		tmpPosition.y += randValueY;
		break;
	case(3):
		tmpPosition.x -= randValueX;
		tmpPosition.y -= randValueY;
		break;
	}
	_owner->SetPosition(tmpPosition);
}

void FallExplosionObjectStateRespawn::SetRandFallSpeed(ExplosionObjectBase* _owner)
{
	_owner->SetFallSpeed((float)(rand() % (int)(1000.0f) + 300.0f));
}
