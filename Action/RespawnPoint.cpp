//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "RespawnPoint.h"
#include "BoxCollider.h"

RespawnPoint::RespawnPoint(const Vector3& _p, const AABB& _box, const Tag& _objectTag)
	: GameObject(false,_objectTag)
	, CorrectionPositionZ(600.0f)
{
	// ポジションの初期化
	position = _p;
	// 高さを補正
	position.z += CorrectionPositionZ;
	// ポジションをセット
	SetPosition(position);

	// 当たり判定用ボックスコライダー付与
	boxCollider = new BoxCollider(this,PhysicsTag::RESPOWN_TAG, GetOnCollisionFunc());
	boxCollider->SetObjectBox(_box);

}

RespawnPoint::~RespawnPoint()
{
}

void RespawnPoint::UpdateGameObject(float _deltaTime)
{
}

void RespawnPoint::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
}
