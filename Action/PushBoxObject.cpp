//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "PushBoxObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"
#include "PushBoardObject.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	object�̃T�C�Y
@param	�I�u�W�F�N�g���ʗptag
@param  �v�b�V���{�[�h���X�V����̂Ɏg�p����f�[�^�\����
*/
PushBoxObject::PushBoxObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, PushBoxData _pushBoxData)
	: GameObject(false, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	isPushBackToPlayer = true;
	isChackGroundToPlayer = true;

	// PushBoard��PushBox�̊Ԋu
	float offsetX = 210.0f;
	float offsetY = 210.0f;
	float offsetZ = 100.0f;

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);

	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/groundModel/box.gpmesh"));

	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();

	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, PhysicsTag::GROUND_TAG, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());

	// �����������Ƃ�PushBoardObject�̈�����ύX���ĕt�^
	if (_pushBoxData.direction.x == 1.0f)
	{
		Vector3 boardSize = Vector3(50.0f, 200.0f, 200.0f);
		new PushBoardObject(Vector3(_p.x + offsetX, _p.y, _p.z + offsetZ), boardSize, PUSH_BOARD, _pushBoxData);
	}

	if (_pushBoxData.direction.x == -1.0f)
	{
		Vector3 boardSize = Vector3(50.0f, 200.0f, 200.0f);
		new PushBoardObject(Vector3(_p.x - offsetX, _p.y, _p.z + offsetZ), boardSize, PUSH_BOARD, _pushBoxData);
	}

	if (_pushBoxData.direction.y == 1.0f)
	{
		Vector3 boardSize = Vector3(200.0f, 50.0f, 200.0f);
		new PushBoardObject(Vector3(_p.x, _p.y + offsetY, _p.z + offsetZ), boardSize, PUSH_BOARD, _pushBoxData);
	}

	if (_pushBoxData.direction.y == -1.0f)
	{
		Vector3 boardSize = Vector3(200.0f, 50.0f, 200.0f);
		new PushBoardObject(Vector3(_p.x, _p.y - offsetY, _p.z + offsetZ), boardSize, PUSH_BOARD, _pushBoxData);
	}
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
PushBoxObject::~PushBoxObject()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void PushBoxObject::UpdateGameObject(float _deltaTime)
{
	//worldbox��n��
	aabb = boxCollider->GetWorldBox();
}