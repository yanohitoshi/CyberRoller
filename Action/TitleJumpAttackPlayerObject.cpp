//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "TitleJumpAttackPlayerObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "TitlePlayerObject.h"
#include "JumpAttackEffectManager.h"

/*
@fn �R���X�g���N�^
@param	�e�N���X�̃|�C���^
@param	�I�u�W�F�N�g�̃T�C�Y
@param	�I�u�W�F�N�g���ʗptag
*/
TitleJumpAttackPlayerObject::TitleJumpAttackPlayerObject(TitlePlayerObject* _ownerObject, const Vector3& _size, const Tag _objectTag)
	: GameObject(false, _objectTag)
	, ShiftPositionZ(100.0f)
{
	ownerObject = _ownerObject;
	position = ownerObject->GetPosition();
	position.z += ShiftPositionZ;
	SetPosition(position);
	SetScale(_size);

	meshComponent = new MeshComponent(this, false, false);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Player/JumpAttackPlayerModel/JumpAttackPlayer.gpmesh"));
	meshComponent->SetVisible(false);
	//���b�V�����擾
	mesh = meshComponent->GetMesh();
	// �P�x�����擾
	luminance = mesh->GetLuminace();
	SetState(State::Disabling);
	new JumpAttackEffectManager(this);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
TitleJumpAttackPlayerObject::~TitleJumpAttackPlayerObject()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void TitleJumpAttackPlayerObject::UpdateGameObject(float _deltaTime)
{
	if (!meshComponent->GetVisible())
	{
		SetPosition(ownerObject->GetPosition());
		SetState(State::Disabling);
	}
	else
	{
		SetState(State::Active);
	}
}

/*
@fn ��]�����֐�
*/
void TitleJumpAttackPlayerObject::RotationProcess(float _angle, Vector3 _axis)
{
	//Z����90�x��]������
	float radian = Math::ToRadians(_angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}
