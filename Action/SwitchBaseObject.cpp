#include "SwitchBaseObject.h"
#include "MeshComponent.h"
#include "SwitchBlock.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "SwitchBlock.h"
#include "Mesh.h"

SwitchBaseObject::SwitchBaseObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Tag& _switchTag)
	: GameObject(false, _objectTag)
{
	// �|�W�V�����E�X�P�[���ETag�̏�����
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);

	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/switch_model/S_EnergySwitch.gpmesh"));
	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();

	// �����蔻��p�{�b�N�X�R���C�_�[��t�^
	boxCollider = new BoxCollider(this, ColliderComponent::SWITCH_BASE, GetOnCollisionFunc());
	// �����蔻��pAABB���쐬
	AABB aabb = { Vector3(-75.0f,-75.0f,-150.0f),Vector3(75.0f,75.0f,40.0f) };
	// �쐬����AABB���Z�b�g
	boxCollider->SetObjectBox(aabb);

	// �X�C�b�`�{�̂�t�^
	new SwitchBlock(this, Vector3(2.6f,2.6f,2.0f), _switchTag);
}

SwitchBaseObject::~SwitchBaseObject()
{
}

void SwitchBaseObject::UpdateGameObject(float _deltaTime)
{
	// ���[���h��Ԃ�AABB���X�V
	aabb = boxCollider->GetWorldBox();
	// �|�W�V�����ɑ��x�𑫂�
	position = position + velocity * _deltaTime;
	// �|�W�V�����̍X�V
	SetPosition(position);

}

void SwitchBaseObject::OnCollision(const GameObject& _hitObject)
{
	// �q�b�g�����I�u�W�F�N�g����������������
	if (_hitObject.GetTag() == Tag::MOVE_GROUND)
	{
		// �������̎����x��t�^
		velocity = _hitObject.GetVelocity();
	}
}
