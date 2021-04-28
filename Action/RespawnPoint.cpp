#include "RespawnPoint.h"
#include "BoxCollider.h"

RespawnPoint::RespawnPoint(const Vector3& _p, const AABB& _box, const Tag& _objectTag)
	: GameObject(false,_objectTag)
{
	// �|�W�V�����̏�����
	position = _p;
	// �|�W�V�������Z�b�g
	SetPosition(position);
	// ���X�|�[���|�C���g�ƂȂ邩�ǂ����t���O�̏�����
	reSpownFlag = false;

	// �����蔻��p�{�b�N�X�R���C�_�[�t�^
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
	// Hit�����烊�X�|�[���|�C���g�ƂȂ邩�ǂ����t���Otrue
	reSpownFlag = true;
}
