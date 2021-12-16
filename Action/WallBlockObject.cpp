//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "WallBlockObject.h"
#include "SkeletalMeshComponent.h"
#include "MeshComponent.h"
#include "MainCameraObject.h"
#include <string>
#include "Skeleton.h"
#include "BoxCollider.h"
#include  "Mesh.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	object�̃T�C�Y
@param	�I�u�W�F�N�g���ʗptag
*/
WallBlockObject::WallBlockObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag) :
	GameObject(false, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	SetPosition(Vector3(_p));
	SetScale(_size);
	tag = _objectTag;
	isPushBackToPlayer = true;
	isPushBackToCamera = true;

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this,false,false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(GRAPHICS_RESOURCE->CreateMesh("Assets/Model/Environment/wall_model/wallBox.gpmesh"));

	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this,PhysicsTag::WALL_TAG,GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());

}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
WallBlockObject::~WallBlockObject()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void WallBlockObject::UpdateGameObject(float _deltaTime)
{
	// ���[���h�{�b�N�X�̍X�V
	aabb = boxCollider->GetWorldBox();
}