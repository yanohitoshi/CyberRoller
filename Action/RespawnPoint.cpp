//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "RespawnPoint.h"
#include "BoxCollider.h"

RespawnPoint::RespawnPoint(const Vector3& _p, const AABB& _box, const Tag& _objectTag)
	: GameObject(false,_objectTag)
{
	// �|�W�V�����̏�����
	position = _p;
	// �|�W�V�������Z�b�g
	SetPosition(position);

	// �����蔻��p�{�b�N�X�R���C�_�[�t�^
	boxCollider = new BoxCollider(this,ColliderComponent::RESPOWN_TAG, GetOnCollisionFunc());
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
}
