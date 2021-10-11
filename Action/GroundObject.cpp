//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GroundObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"
#include "GeometryInstanceComponent.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	object�̃T�C�Y
@param	�I�u�W�F�N�g���ʗptag
@param	���C�g�t���ۂ�
*/
GroundObject::GroundObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag)
	: GameObject(false, _objectTag)
	, CorrectionAabbValue(0.1f)
{
	//GameObject�����o�ϐ��̏�����
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	isPushBackToPlayer = true;
	isChackGroundToPlayer = true;
	isPushBackToCamera = true;
	////���f���`��p�̃R���|�[�l���g
	//meshComponent = new MeshComponent(this,false,false);
	////Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	//meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/groundModel/normalGround.gpmesh"));
	//meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/groundModel/lightGround.gpmesh"));

	geometryInstanceComponent = new GeometryInstanceComponent(this, RENDERER->GetMesh("Assets/Model/Environment/groundModel/normalGround.gpmesh"), GeometryInstanceType::gGround,500);
	geometryInstanceComponent->AddGeometryInstanceManager();

	//���b�V�����擾
	mesh = geometryInstanceComponent->GetMesh();
	// �P�x�����擾
	luminance = mesh->GetLuminace();

	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this,PhysicsTag::GROUND_TAG, GetOnCollisionFunc());
	aabb = mesh->GetBox();

	//�v���C���[�����蔲���Ȃ��悤��AABB�̃T�C�Y��␳
	aabb.max.y += CorrectionAabbValue;
	aabb.min.y -= CorrectionAabbValue;
	boxCollider->SetObjectBox(aabb);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
GroundObject::~GroundObject()
{
	//geometryInstanceComponent->RemoveGeometryInstanceManager();
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void GroundObject::UpdateGameObject(float _deltaTime)
{
	//worldbox��n��
	aabb = boxCollider->GetWorldBox();
}