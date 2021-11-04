#include "ExplosionArea.h"
#include "ExplosionObject.h"
#include "SphereCollider.h"

ExplosionArea::ExplosionArea(const Tag& _objectTag, ExplosionObject* _owner)
	:GameObject(false, _objectTag)
	, owner(_owner)
	, ExplosionAreaSize(100.0f)
{
	SetState(State::Active);
	SetPosition(owner->GetPosition());

	//ƒWƒƒƒ“ƒvUŒ‚”»’è—p‚ÌsphereCollider
	sphereCollider = new SphereCollider(this, PhysicsTag::EXPLOSION_AREA_TAG, GetOnCollisionFunc());
	Sphere sphere = { Vector3(0.0f,0.0f,0.0f),ExplosionAreaSize };
	sphereCollider->SetObjectSphere(sphere);
}

ExplosionArea::~ExplosionArea()
{
}

void ExplosionArea::UpdateGameObject(float _deltaTime)
{
	SetPosition(owner->GetPosition());
	if (owner->GetIsExplode())
	{
		SetState(State::Active);
	}
	else
	{
		SetState(State::Disabling);
	}
}

void ExplosionArea::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
}
