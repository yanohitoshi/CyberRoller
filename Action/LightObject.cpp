//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "LightObject.h"
#include "Mesh.h"
#include <string>
#include "MeshComponent.h"
#include "Renderer.h"

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
	//geometryInstanceComponent = new GeometryInstanceComponent(this, RENDERER->GetMesh("Assets/Model/Environment/groundModel/normalGround.gpmesh"), GeometryInstanceType::gGround);
	//geometryInstanceComponent->AddGeometryInstanceManager();


	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/LightObject/PowerCells/SM_PowerCells_Floor.gpmesh"));
	//���b�V�����擾
	mesh = meshComponent->GetMesh();
	// �P�x�����擾
	luminance = mesh->GetLuminace();
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
LightObject::~LightObject()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void LightObject::UpdateGameObject(float _deltaTime)
{
}
