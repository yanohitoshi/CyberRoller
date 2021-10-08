//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "GroundObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	object�̃T�C�Y
@param	�I�u�W�F�N�g���ʗptag
@param	���C�g�t���ۂ�
*/
GroundObject::GroundObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, bool _isLight)
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
	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this,false,false);

	if (_isLight)
	{
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/groundModel/lightGround.gpmesh"));
	}
	else
	{
		//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/groundModel/normalGround.gpmesh"));
	}

	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
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