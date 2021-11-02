#include "ExplosionObjectStateRespawn.h"
#include "MeshComponent.h"

ExplosionObjectState ExplosionObjectStateRespawn::Update(ExplosionObject* _owner, float _deltaTime)
{
	++respawnCount;

	if (respawnCount > 60)
	{
		_owner->SetPosition(_owner->GetFirstPosition());
		meshComponent->SetVisible(true);
		_owner->SetState(State::Active);
		_owner->SetIsExplode(false);
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
