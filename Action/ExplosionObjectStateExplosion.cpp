#include "ExplosionObjectStateExplosion.h"
#include "MeshComponent.h"

ExplosionObjectState ExplosionObjectStateExplosion::Update(ExplosionObject* _owner, float _deltaTime)
{
	++explosionCount;
	if (explosionCount >= 10)
	{
		state = ExplosionObjectState::RESPAWN;
	}

	return state;
}

void ExplosionObjectStateExplosion::Enter(ExplosionObject* _owner, float _deltaTime)
{
	state = ExplosionObjectState::EXPLOSION;
	explosionCount = 0;
	meshComponent = _owner->GetMeshComponent();
	meshComponent->SetVisible(false);
	_owner->SetIsStartExplosion(false);
	_owner->SetIsExplode(true);
}