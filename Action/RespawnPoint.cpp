#include "RespawnPoint.h"
#include "BoxCollider.h"

RespawnPoint::RespawnPoint(const Vector3& _p, const AABB& _box, const Tag& _objectTag)
	: GameObject(false,_objectTag)
{
	// ポジションの初期化
	position = _p;
	// ポジションをセット
	SetPosition(position);
	// リスポーンポイントとなるかどうかフラグの初期化
	reSpownFlag = false;

	// 当たり判定用ボックスコライダー付与
	boxCollider = new BoxCollider(this,ColliderComponent::ReSpownTag, GetOnCollisionFunc());
	boxCollider->SetObjectBox(_box);

}

RespawnPoint::~RespawnPoint()
{
}

void RespawnPoint::UpdateGameObject(float _deltaTime)
{
}

void RespawnPoint::OnCollision(const GameObject& _hitObject)
{
	// Hitしたらリスポーンポイントとなるかどうかフラグtrue
	reSpownFlag = true;
}
