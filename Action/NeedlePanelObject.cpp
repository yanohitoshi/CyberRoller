//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "NeedlePanelObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "RenderingObjectManager.h"
#include "BoxCollider.h"
#include "NeedleObject.h"
#include "GeometryInstanceComponent.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	object�̃T�C�Y
@param	�I�u�W�F�N�g���ʗptag
*/
NeedlePanelObject::NeedlePanelObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag) :
	GameObject(false, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;

	// �W�I���g���C���X�^���X�R���|�[�l���g�𐶐�
	geometryInstanceComponent = new GeometryInstanceComponent(this, RENDERING_OBJECT_MANAGER->CreateMesh("Assets/Model/Environment/Ground/model/lightGround.gpmesh"), GeometryInstanceType::G_NEEDLE_PANEL);
	// �W�I���g���C���X�^���X�}�l�[�W���[�N���X�ɒǉ�
	geometryInstanceComponent->AddGeometryInstanceManager();
	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, PhysicsTag::NEEDLE_TAG, GetOnCollisionFunc());
	AABB box = { Vector3(-0.8f,-0.8f,-1.0f),Vector3(0.8f,0.8f,8.0f) };
	boxCollider->SetObjectBox(box);

	new NeedleObject(this, Vector3(0.0f, 0.0f, 50.0f), Vector3(2.5f, 2.5f, 2.0f), Tag::NEEDLE);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
NeedlePanelObject::~NeedlePanelObject()
{
	geometryInstanceComponent->RemoveGeometryInstanceManager();
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void NeedlePanelObject::UpdateGameObject(float _deltaTime)
{
	//worldbox��n��
	aabb = boxCollider->GetWorldBox();
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
void NeedlePanelObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// �q�b�g�����I�u�W�F�N�g����������������
	if (_hitObject.GetTag() == Tag::MOVE_GROUND)
	{
		// �������̑��x��t�^
		velocity = _hitObject.GetVelocity();
	}
}
