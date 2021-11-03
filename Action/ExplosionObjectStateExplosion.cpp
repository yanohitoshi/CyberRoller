#include "ExplosionObjectStateExplosion.h"
#include "MeshComponent.h"

ExplosionObjectState ExplosionObjectStateExplosion::Update(ExplosionObject* _owner, float _deltaTime)
{
	++explosionCount;

	if (explosionCount > 60)
	{
		state = ExplosionObjectState::RESPAWN;
	}

	return state;
}

void ExplosionObjectStateExplosion::Enter(ExplosionObject* _owner, float _deltaTime)
{
	state = ExplosionObjectState::EXPLOSION;
	meshComponent = _owner->GetMeshComponent();
	meshComponent->SetVisible(false);
	_owner->SetIsExplode(true);
}