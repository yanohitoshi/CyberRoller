//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "JumpSwitchObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"

JumpSwitchObject::JumpSwitchObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag)
	: GameObject(false, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/jumpSwitch_model/jumpSwitch.gpmesh"));

	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, ColliderComponent::JUMP_SWITCH_TAG, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());

}

JumpSwitchObject::~JumpSwitchObject()
{
}

void JumpSwitchObject::UpdateGameObject(float _deltaTime)
{
	// �|�W�V�����ɑ��x�𑫂�
	position = position + velocity * _deltaTime;
	// �|�W�V�������X�V
	SetPosition(position);
}

void JumpSwitchObject::OnCollision(const GameObject& _hitObject)
{
	// �q�b�g�����I�u�W�F�N�g����������������
	if (_hitObject.GetTag() == Tag::MOVE_GROUND)
	{
		// �������̎����x��t�^
		velocity = _hitObject.GetVelocity();
	}
}
