#include "LightPositionChangePoint.h"
#include "BoxCollider.h"

LightPositionChangePoint::LightPositionChangePoint(const Vector3& _p, const AABB& _box, const Tag& _objectTag)
	: GameObject(false, _objectTag)
	, ShiftPositionZ(5000.0f)
{
	// �|�W�V�����̏�����
	position = _p;
	//position.z += ShiftPositionZ;
	// �|�W�V�������Z�b�g
	SetPosition(position);

	// ���X�|�[���|�C���g�ƂȂ邩�ǂ����t���O�̏�����
	reSpownFlag = false;

	// �����蔻��p�{�b�N�X�R���C�_�[�t�^
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
