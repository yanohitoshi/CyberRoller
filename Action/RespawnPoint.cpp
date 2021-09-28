//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "RespawnPoint.h"
#include "BoxCollider.h"

RespawnPoint::RespawnPoint(const Vector3& _p, const AABB& _box, const Tag& _objectTag)
	: GameObject(false,_objectTag)
	, CorrectionPositionZ(600.0f)
{
	// �|�W�V�����̏�����
	position = _p;
	// ������␳
	position.z += CorrectionPositionZ;
	// �|�W�V�������Z�b�g
	SetPosition(position);

	// �����蔻��p�{�b�N�X�R���C�_�[�t�^
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
