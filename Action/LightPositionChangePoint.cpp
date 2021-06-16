#include "LightPositionChangePoint.h"
#include "BoxCollider.h"

LightPositionChangePoint::LightPositionChangePoint(const Vector3& _p, const AABB& _box, const Tag& _objectTag)
	: GameObject(false, _objectTag)
	, ShiftPositionZ(5000.0f)
{
	// ポジションの初期化
	position = _p;
	//position.z += ShiftPositionZ;
	// ポジションをセット
	SetPosition(position);

	// リスポーンポイントとなるかどうかフラグの初期化
	reSpownFlag = false;

	// 当たり判定用ボックスコライダー付与
	boxCollider = new BoxCollider(this, ColliderComponent::RESPOWN_TAG, GetOnCollisionFunc());
	boxCollider->SetObjectBox(_box);

}

LightPositionChangePoint::~LightPositionChangePoint()
{
}

void LightPositionChangePoint::UpdateGameObject(float _deltaTime)
{
}

void LightPositionChangePoint::OnCollision(const GameObject& _hitObject)
{
}
