//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "JumpSwitchObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "RenderingObjectManager.h"
#include "BoxCollider.h"
#include "GeometryInstanceComponent.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	object�̃T�C�Y
@param	�I�u�W�F�N�g���ʗptag
*/
JumpSwitchObject::JumpSwitchObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag)
	: GameObject(false, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;

	// �W�I���g���C���X�^���X�R���|�[�l���g�𐶐�
	geometryInstanceComponent = new GeometryInstanceComponent(this, RENDERING_OBJECT_MANAGER->CreateMesh("Assets/Model/Environment/JumpSwitch/model/jumpSwitch.gpmesh"), GeometryInstanceType::G_JUMP_SWITCH);
	// �W�I���g���C���X�^���X�}�l�[�W���[�N���X�ɒǉ�
	geometryInstanceComponent->AddGeometryInstanceManager();

	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = geometryInstanceComponent->GetMesh();
	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, PhysicsTag::JUMP_SWITCH_TAG, GetOnCollisionFunc());
	AABB aabb = { mesh->GetBox() };
	aabb.min.z -= 5.0f;
	boxCollider->SetObjectBox(aabb);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
JumpSwitchObject::~JumpSwitchObject()
{
	geometryInstanceComponent->RemoveGeometryInstanceManager();
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void JumpSwitchObject::UpdateGameObject(float _deltaTime)
{
	// �|�W�V�����ɑ��x�𑫂�
	position = position + velocity * _deltaTime;
	// �|�W�V�������X�V
	SetPosition(position);
}

/*
@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
@param	��������GameObject
@param	��������GameObject�̓����蔻��^�O
*/
void JumpSwitchObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// �q�b�g�����I�u�W�F�N�g����������������
	if (_hitObject.GetTag() == Tag::MOVE_GROUND)
	{
		// �������̎����x��t�^
		velocity = _hitObject.GetVelocity();
	}
}