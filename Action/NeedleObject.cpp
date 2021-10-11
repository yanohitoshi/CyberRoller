//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "NeedleObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"
#include "GeometryInstanceComponent.h"

/*
@fn �R���X�g���N�^
@param	�e�ƂȂ�object�̃|�C���^
@param	�eobject�Ƃ̊Ԋu
@param	object�̃T�C�Y
@param	�I�u�W�F�N�g���ʗptag
*/
NeedleObject::NeedleObject(GameObject* _owner ,const Vector3& _offset, const Vector3& _size, const Tag& _objectTag) :
	GameObject(false, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	position = _owner->GetPosition() + _offset;
	SetPosition(position);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	owner = _owner;
	////���f���`��p�̃R���|�[�l���g
	//meshComponent = new MeshComponent(this, false, false);
	////Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	//meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/goods_model/needles.gpmesh"));
	geometryInstanceComponent = new GeometryInstanceComponent(this, RENDERER->GetMesh("Assets/Model/Environment/goods_model/needles.gpmesh"), GeometryInstanceType::G_NEEDLE);
	geometryInstanceComponent->AddGeometryInstanceManager();
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
NeedleObject::~NeedleObject()
{
	geometryInstanceComponent->RemoveGeometryInstanceManager();
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void NeedleObject::UpdateGameObject(float _deltaTime)
{
	// owner�̑��x��t�^
	velocity = owner->GetVelocity();

	// �|�W�V�����ɑ��x�𑫂�
	position = position + velocity * _deltaTime;

	// �|�W�V�������X�V
	SetPosition(position);
}
