#include "NextSceneObject.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Mesh.h"
#include "PlayerObject.h"
#include "MainCameraObject.h"
#include "CrystalEffectManager.h"


NextSceneObject::NextSceneObject(const Vector3& _pos, const Tag& _objectTag, PlayerObject* _playerObject)
	: GameObject(false, _objectTag)
	, Angle(15.0f)
	, MoveSpeed(20.0f)
	, CalculationDrawEndPosition(3000.0f)
{

	//GameObject�����o�ϐ��̏�����
	SetPosition(_pos);
	SetScale(Vector3(50.0f, 50.0f, 50.0f));
	firstPos = _pos;
	tag = _objectTag;
	state = Active;
	velocity = Vector3(0.0f, 0.0f, 0.0f);

	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);
	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/goods_model/SM_Gems_01a.gpmesh"));
	//���b�V������AABB�Ŏg��x,y,z��min��max���擾����
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();

	playerObject = _playerObject;

	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, ColliderComponent::CLEAR_POINT_TAG, GetOnCollisionFunc());
	AABB aabb = { Vector3(-1.0f,-1.0f,-1.0f),Vector3(1.0f,1.0f,3.0f) };
	boxCollider->SetObjectBox(aabb);

	// 4�F�̃G�t�F�N�g��t�^
	new CrystalEffectManager(this,CrystalColor::WHITE);
	new CrystalEffectManager(this, CrystalColor::RED);
	new CrystalEffectManager(this, CrystalColor::BLUE);
	new CrystalEffectManager(this, CrystalColor::GREEN);
}

NextSceneObject::~NextSceneObject()
{

}

void NextSceneObject::UpdateGameObject(float _deltaTime)
{
	if (playerObject->GetClearFlag() == true)
	{
		// ���x�t�^
		velocity.z = MoveSpeed;
		
		// ��]����
		RotationProcess();

		// ������
		MovableProcess();

		// �J�����ɒ���������̂Ń|�W�V������n��
		mainCamera->SetLerpObjectPos(position);
	}


}

void NextSceneObject::RotationProcess()
{
	//Z�����w��p�x��]������
	float radian = Math::ToRadians(Angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);

}

void NextSceneObject::MovableProcess()
{
	// �|�W�V�����ɑ��x�𑫂�
	position += velocity;
	// �|�W�V�������X�V
	SetPosition(position);

	// ��ʒu�܂œ͂�����`��J�b�g
	if (position.z >= firstPos.z + CalculationDrawEndPosition)
	{
		meshComponent->SetVisible(false);
	}

}

void NextSceneObject::OnCollision(const GameObject& _hitObject)
{
}
