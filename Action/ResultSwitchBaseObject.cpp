#include "ResultSwitchBaseObject.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "ResultSwitchObject.h"

ResultSwitchBaseObject::ResultSwitchBaseObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Tag& _switchTag)
	: GameObject(false, _objectTag)
	, Angle(90.0f)
{
	// �|�W�V�����E�X�P�[���ETag�̏�����
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	isPushBackToPlayer = true;
	isChackGroundToPlayer = true;
	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);

	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/switch_model/S_EnergySwitch.gpmesh"));

	//Z����90�x��]������
	float radian = Math::ToRadians(Angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitY, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);

	// ���U���g�p�̃X�C�b�`�{�̂𐶐�
	new ResultSwitchObject(this, Vector3(2.6f, 2.6f, 2.0f), tag, Angle);
	
}

ResultSwitchBaseObject::~ResultSwitchBaseObject()
{
}

void ResultSwitchBaseObject::UpdateGameObject(float _deltaTime)
{
}
