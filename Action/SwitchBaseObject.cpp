//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "SwitchBaseObject.h"
#include "MeshComponent.h"
#include "SwitchBlock.h"
#include "BoxCollider.h"
#include "SwitchBlock.h"
#include "ResultSwitchObject.h"
#include "Mesh.h"
#include "GeometryInstanceComponent.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	object�̃T�C�Y
@param	�I�u�W�F�N�g���ʗptag
@param  �ǂ̋��̃X�C�b�`�Ȃ̂��𔻕ʂ�����悤��Tag
@param	�`���[�g���A���pSwitch���ǂ����̃t���O
*/
SwitchBaseObject::SwitchBaseObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Tag& _switchTag , bool _isTutorial)
	: GameObject(false, _objectTag)
	, Angle(90.0f)
{
	// �|�W�V�����E�X�P�[���ETag�̏�����
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	//isPushBackToPlayer = true;
	isCheckGroundToPlayer = true;

	// �W�I���g���C���X�^���X�R���|�[�l���g�𐶐�
	geometryInstanceComponent = new GeometryInstanceComponent(this, GRAPHICS_RESOURCE->CreateMesh("Assets/Model/Environment/Switch/model/S_EnergySwitch.gpmesh"), GeometryInstanceType::G_BASE_SWITCH);
	// �W�I���g���C���X�^���X�}�l�[�W���[�N���X�ɒǉ�
	geometryInstanceComponent->AddGeometryInstanceManager();

	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = geometryInstanceComponent->GetMesh();

	// �����蔻��p�{�b�N�X�R���C�_�[��t�^
	boxCollider = new BoxCollider(this, PhysicsTag::SWITCH_BASE_TAG, GetOnCollisionFunc());
	// �����蔻��pAABB���쐬
	AABB aabb = { Vector3(-75.0f,-75.0f,-150.0f),Vector3(75.0f,75.0f,40.0f) };
	// �쐬����AABB���Z�b�g
	boxCollider->SetObjectBox(aabb);

	// �X�C�b�`�{�̂�t�^
	new SwitchBlock(this, Vector3(2.6f,2.6f,2.0f), _switchTag, _isTutorial);
	
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
SwitchBaseObject::~SwitchBaseObject()
{
	geometryInstanceComponent->RemoveGeometryInstanceManager();
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void SwitchBaseObject::UpdateGameObject(float _deltaTime)
{
	// ���[���h��Ԃ�AABB���X�V
	aabb = boxCollider->GetWorldBox();
	// �|�W�V�����ɑ��x�𑫂�
	position = position + velocity * _deltaTime;
	// �|�W�V�����̍X�V
	SetPosition(position);
}

/*
@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�
@param	��������GameObject
@param	��������GameObject�̓����蔻��^�O
*/
void SwitchBaseObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// �q�b�g�����I�u�W�F�N�g����������������
	if (_hitObject.GetTag() == Tag::MOVE_GROUND)
	{
		// �������̎����x��t�^
		velocity = _hitObject.GetVelocity();
	}
}