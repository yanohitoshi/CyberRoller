//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "LineSegmentCollider.h"
#include "Math.h"
#include "GameObject.h"
#include "Collision.h"
#include "Game.h"
#include "MainCameraObject.h"

LineSegmentCollider::LineSegmentCollider(GameObject* _owner, ColliderComponent::PhysicsTag tag, onCollisionFunc _func, int _updateOrder, int _collisionOrder)
	: ColliderComponent(_owner,tag, _updateOrder, _collisionOrder)
	, objectLineSegment({ Vector3::Zero, Vector3::Zero })
	, worldLineSegment({Vector3::Zero, Vector3::Zero})
	, value(0.0f)
	,forwardVec(Vector3::Zero)
	, contactPoint(0.0f)
{
	PHYSICS->AddLineSegment(this, _func);
}


LineSegmentCollider::~LineSegmentCollider()
{
	PHYSICS->RemoveLineSegment(this);
}

void LineSegmentCollider::OnUpdateWorldTransform()
{
	mainCamera = GameObject::GetMainCamera();

	worldLineSegment = objectLineSegment;

	point = mainCamera->GetlerpObjectPos();
	worldLineSegment.start += point;
	worldLineSegment.end += owner->GetPosition();

	PHYSICS->HitCheck(this);
}
