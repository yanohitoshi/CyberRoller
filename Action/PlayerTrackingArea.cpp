#include "PlayerTrackingArea.h"
#include "TrackingEnemyObject.h"
#include "SphereCollider.h"

PlayerTrackingArea::PlayerTrackingArea(const Tag& _objectTag, TrackingEnemyObject* _ownerEnemy, float _areaValue)
	:GameObject(false, _objectTag)
	, ownerEnemy(_ownerEnemy)
{
	SetPosition(ownerEnemy->GetPosition());

	//ジャンプ攻撃判定用のsphereCollider
	sphereCollider = new SphereCollider(this, PhysicsTag::PLAYER_TRACKING_AREA_TAG, GetOnCollisionFunc());
	Sphere sphere = { Vector3(0.0f,0.0f,0.0f),_areaValue };
	sphereCollider->SetObjectSphere(sphere);
}

PlayerTrackingArea::~PlayerTrackingArea()
{
}

void PlayerTrackingArea::UpdateGameObject(float _deltaTime)
{
	// ポジションを固定
	SetPosition(position);
}

void PlayerTrackingArea::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// プレイヤーを見つけたら
	if (_hitObject.GetTag() == Tag::PLAYER)
	{
		// 親クラスを追跡状態にセット
		ownerEnemy->SetIsTracking(true);
	}
}
