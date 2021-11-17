#include "FallExplosionArea.h"
#include "FallExplosionObject.h"
#include "BoxCollider.h"

FallExplosionArea::FallExplosionArea(const Vector3& _pos, const Tag _objectTag,Vector3& _area, int _quantity)
	: GameObject(false, _objectTag)
	, area(Vector3::Zero)
{
	position = _pos;
	SetPosition(position);
	quantity = _quantity;
	isFallStart = false;
	area = _area;
	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::FALL_BOMB_AREA_TAG, GetOnCollisionFunc());
	AABB aabb = { _area * -1.0f,_area };
	boxCollider->SetObjectBox(aabb);

	fallExplosionObjects.resize(quantity);

	for (int i = 0; i < quantity; i++)
	{
		fallExplosionObjects[i] = new FallExplosionObject(this, position, Tag::FALL_BOMB);
	}

}

FallExplosionArea::~FallExplosionArea()
{
}

void FallExplosionArea::UpdateGameObject(float _deltaTime)
{
	if (isFallStart)
	{
		isFallStart = false;
	}
}

void FallExplosionArea::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	if (_physicsTag == PhysicsTag::PLAYER_TAG)
	{
		isFallStart = true;
	}
}
