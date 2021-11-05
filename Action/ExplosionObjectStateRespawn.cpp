#include "ExplosionObjectStateRespawn.h"
#include "MeshComponent.h"

ExplosionObjectState ExplosionObjectStateRespawn::Update(ExplosionObject* _owner, float _deltaTime)
{
	++respawnCount;

	if (respawnCount > 240)
	{
		_owner->SetPosition(_owner->GetFirstPosition());
		_owner->SetIsHitExplosionObject(false);
		meshComponent->SetVisible(true);
		meshComponent->SetEmissiveColor(EmissiveColorBlue);
		_owner->SetState(State::Active);
		_owner->SetRotation(Quaternion::Identity);
		_owner->SetScaleZ(5.0f);
		state = ExplosionObjectState::IDLE;
	}
	return state;
}

void ExplosionObjectStateRespawn::Enter(ExplosionObject* _owner, float _deltaTime)
{
	state = ExplosionObjectState::RESPAWN;
	_owner->GetFirstPosition();
	respawnCount = 0;
	meshComponent = _owner->GetMeshComponent();
	_owner->SetIsExplode(false);
}
