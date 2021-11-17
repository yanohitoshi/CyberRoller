#include "ExplosionObjectStateRespawn.h"
#include "MeshComponent.h"

ExplosionObjectState ExplosionObjectStateRespawn::Update(ExplosionObjectBase* _owner, float _deltaTime)
{
	++respawnCount;

	if (respawnCount > 240)
	{
		_owner->SetIsHitExplosionObject(false);
		meshComponent->SetVisible(true);
		meshComponent->SetEmissiveColor(EmissiveColorBlue);
		_owner->SetRotation(Quaternion::Identity);
		_owner->SetScaleZ(5.0f);
		_owner->SetPosition(firstPosition);
		state = ExplosionObjectState::IDLE;
	}

	return state;
}

void ExplosionObjectStateRespawn::Enter(ExplosionObjectBase* _owner, float _deltaTime)
{
	state = ExplosionObjectState::RESPAWN;
	firstPosition = _owner->GetFirstPosition();
	respawnCount = 0;
	meshComponent = _owner->GetMeshComponent();
	_owner->SetIsExplode(false);
	_owner->SetState(State::Disabling);
}
