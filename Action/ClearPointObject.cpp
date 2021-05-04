#include "ClearPointObject.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Mesh.h"
#include "PlayerObject.h"
#include "MainCameraObject.h"
#include "GameClearEffectManeger.h"
#include "CrystalEffectManager.h"

ClearPointObject::ClearPointObject(const Vector3& _pos, const Tag& _objectTag)
	: GameObject(false,_objectTag)
	, Angle(10.0f)
	, MoveSpeed(50.0f)
{

	//GameObject�����o�ϐ��̏�����
	SetPosition(_pos);
	SetScale(Vector3(50.0f, 50.0f, 50.0f));
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

	//�����蔻��p�̃R���|�[�l���g
	boxCollider = new BoxCollider(this, ColliderComponent::ClearPointTag, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());

	new GameClearEffectManeger(this);

	// 4�F�̃G�t�F�N�g��t�^
	new CrystalEffectManager(this, CrystalColor::WHITE);
	new CrystalEffectManager(this, CrystalColor::RED);
	new CrystalEffectManager(this, CrystalColor::BLUE);
	new CrystalEffectManager(this, CrystalColor::GREEN);


}

ClearPointObject::~ClearPointObject()
{

}

void ClearPointObject::UpdateGameObject(float _deltaTime)
{
	if (PlayerObject::GetClearFlag() == true)
	{
		// ���x��t�^
		velocity.z = MoveSpeed;

		//Z����10�x��]������
		float radian = Math::ToRadians(Angle);
		Quaternion rot = this->GetRotation();
		Quaternion inc(Vector3::UnitZ, radian);
		Quaternion target = Quaternion::Concatenate(rot, inc);
		SetRotation(target);

		// �|�W�V�����ɑ��x�𑫂�
		position += velocity;
		// �|�W�V�������X�V
		SetPosition(position);
		// �J�����ɒ���������̂Ń|�W�V������n��
		mainCamera->SetLerpObjectPos(position);

	}
}

void ClearPointObject::OnCollision(const GameObject& _hitObject)
{
}

