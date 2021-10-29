#include "CameraChangePoint.h"
#include "BoxCollider.h"
#include "CameraObjectStateBase.h"

CameraChangePoint::CameraChangePoint(const Vector3& _p, const AABB& _box, Vector3& _changeOffset,const Tag& _objectTag)
	: GameObject(false, _objectTag)
{
	// ポジションの初期化
	position = _p;
	changeOffset = _changeOffset;
	// ポジションをセット
	SetPosition(position);

	// 当たり判定用ボックスコライダー付与
	boxCollider = new BoxCollider(this, PhysicsTag::CAMERA_MODE_CHANGE_AREA, GetOnCollisionFunc());
	boxCollider->SetObjectBox(_box);
}

CameraChangePoint::~CameraChangePoint()
{
}

void CameraChangePoint::UpdateGameObject(float _deltaTime)
{
}

void CameraChangePoint::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	if (_physicsTag == PhysicsTag::PLAYER_TAG)
	{
		mainCamera->SetNextState(CameraState::LANDSCAPE);
		mainCamera->SetOffsetPosition(changeOffset);
	}
}
