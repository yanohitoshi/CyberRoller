#include "CameraChangePoint.h"
#include "BoxCollider.h"
#include "CameraObjectBase.h"

CameraChangePoint::CameraChangePoint(const Vector3& _p, const AABB& _box, const Tag& _objectTag)
	: GameObject(false, _objectTag)
{
	// �|�W�V�����̏�����
	position = _p;

	// �|�W�V�������Z�b�g
	SetPosition(position);

	// �����蔻��p�{�b�N�X�R���C�_�[�t�^
	boxCollider = new BoxCollider(this, PhysicsTag::CAMERA_MODE_BEHIND_AREA, GetOnCollisionFunc());
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
		mainCamera->SetCameraMode(CameraMode::BEHIND);
	}
}
