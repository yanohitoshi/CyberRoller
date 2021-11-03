#include "ExplosionObjectStateRespawn.h"
#include "MeshComponent.h"

ExplosionObjectState ExplosionObjectStateRespawn::Update(ExplosionObject* _owner, float _deltaTime)
{
	++respawnCount;

	if (respawnCount > 60)
	{
		_owner->SetPosition(_owner->GetFirstPosition());
		_owner->SetIsExplode(false);
		_owner->SetIsHitExplosionObject(false);
		meshComponent->SetEmissiveColor(EmissiveColorBlue);
		meshComponent->SetVisible(true);
		_owner->SetState(State::Active);
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
}
