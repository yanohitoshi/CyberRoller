#include "PlayerTrackingArea.h"
#include "TrackingEnemyObject.h"
#include "SphereCollider.h"

PlayerTrackingArea::PlayerTrackingArea(const Tag& _objectTag, TrackingEnemyObject* _ownerEnemy)
	:GameObject(false, _objectTag)
	, ownerEnemy(_ownerEnemy)
{
	SetPosition(ownerEnemy->GetPosition());

	//ƒWƒƒƒ“ƒvUŒ‚”»’è—p‚ÌsphereCollider
	sphereCollider = new SphereCollider(this, PhysicsTag::PLAYER_TRACKING_AREA_TAG, GetOnCollisionFunc());
	Sphere sphere = { Vector3(0.0f,0.0f,0.0f),1200.0f };
	sphereCollider->SetObjectSphere(sphere);
}

PlayerTrackingArea::~PlayerTrackingArea()
{
}

void PlayerTrackingArea::UpdateGameObject(float _deltaTime)
{
	SetPosition(ownerEnemy->GetPosition());
}

void PlayerTrackingArea::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	if (_hitObject.GetTag() == Tag::PLAYER)
	{
		ownerEnemy->SetIsTracking(true);
	}
}
