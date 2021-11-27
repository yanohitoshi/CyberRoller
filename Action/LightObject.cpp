//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "LightObject.h"
#include "Mesh.h"
#include <string>
#include "MeshComponent.h"
#include "RenderingObjectManager.h"
#include "GeometryInstanceComponent.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	object�̃T�C�Y
@param	�I�u�W�F�N�g���ʗptag
@param	�E���ɓY�킹�邩�ǂ���
*/
LightObject::LightObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, bool _isRight)
	: GameObject(false, _objectTag)
	, ShiftPositionX(195.0f)
	, ShiftRightPositionY(50.0f)
	, ShiftLeftPositionY(200.0f)
	, ShiftPositionZ(110.0f)
{
	//GameObject�����o�ϐ��̏�����
	position = _p;
	position.x += ShiftPositionX;
	position.z -= ShiftPositionZ;

	// �E���Ɋ񂹂邩�����Ɋ񂹂邩��������|�W�V���������炷
	if (_isRight)
	{
		position.y += ShiftRightPositionY;
	}
	else
	{
		position.y -= ShiftLeftPositionY;
	}

	SetPosition(position);
	SetScale(_size);
	tag = _objectTag;
	state = Active;

	// �W�I���g���C���X�^���X�R���|�[�l���g�𐶐�
	geometryInstanceComponent = new GeometryInstanceComponent(this, RENDERING_OBJECT_MANAGER->CreateMesh("Assets/Model/Environment/Light/model/SM_PowerCells_Floor.gpmesh"), GeometryInstanceType::G_LIGHT,300);
	// �W�I���g���C���X�^���X�}�l�[�W���[�N���X�ɒǉ�
	geometryInstanceComponent->AddGeometryInstanceManager();

	//���b�V�����擾
	mesh = geometryInstanceComponent->GetMesh();
	// �P�x�����擾
	luminance = mesh->GetLuminace();
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
LightObject::~LightObject()
{
	geometryInstanceComponent->RemoveGeometryInstanceManager();
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void LightObject::UpdateGameObject(float _deltaTime)
{
}
