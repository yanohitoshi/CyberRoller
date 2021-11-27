//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "ResultSwitchBaseObject.h"
#include "MeshComponent.h"
#include "RenderingObjectManager.h"
#include "ResultSwitchObject.h"

/*
@fn �R���X�g���N�^
@param	�|�W�V����
@param	object�̃T�C�Y
@param	�I�u�W�F�N�g���ʗptag
*/
ResultSwitchBaseObject::ResultSwitchBaseObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag)
	: GameObject(false, _objectTag)
	, Angle(90.0f)
{
	// �|�W�V�����E�X�P�[���ETag�̏�����
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	isPushBackToPlayer = true;
	isCheckGroundToPlayer = true;
	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);

	meshComponent->SetMesh(RENDERING_OBJECT_MANAGER->GetMesh("Assets/Model/Switch/model/S_EnergySwitch.gpmesh"));

	//Z����90�x��]������
	float radian = Math::ToRadians(Angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitY, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);

	// ���U���g�p�̃X�C�b�`�{�̂𐶐�
	new ResultSwitchObject(this, Vector3(2.6f, 2.6f, 2.0f), tag, Angle);
	
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
ResultSwitchBaseObject::~ResultSwitchBaseObject()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void ResultSwitchBaseObject::UpdateGameObject(float _deltaTime)
{
}
