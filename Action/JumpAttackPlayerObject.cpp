#include "JumpAttackPlayerObject.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "SphereCollider.h"
#include "JumpAttackEffectManager.h"

JumpAttackPlayerObject::JumpAttackPlayerObject(PlayerObject* _ownerObject, const Vector3& _size, const Tag _objectTag)
	: GameObject(false, _objectTag)
	, Rotation(10.0f)
{
	ownerObject = _ownerObject;
	position = ownerObject->GetPosition();
	position.z += 100.0f;
	rotationAngle = 0.0f;
	// 前方ベクトル初期化
	forwardVec = ownerObject->GetForwardVec();

	SetPosition(position);
	SetScale(_size);
	SetState(State::Disabling);
	tmpState = State::Disabling;

	meshComponent = new MeshComponent(this, false, false);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Player/JumpAttackPlayerModel/JumpAttackPlayer.gpmesh"));

	//接地判定用のsphereCollider
	sphereCollider = new SphereCollider(this, PhysicsTag::JUMP_ATTACK_PLAYER_TAG, GetOnCollisionFunc());
	Sphere jumpAttackSphere = { Vector3(0.0f,0.0f,0.0f),3.0f };
	sphereCollider->SetObjectSphere(jumpAttackSphere);

	new JumpAttackEffectManager(this);
}

JumpAttackPlayerObject::~JumpAttackPlayerObject()
{
}

void JumpAttackPlayerObject::UpdateGameObject(float _deltaTime)
{

	if (ownerObject->GetNowState() == PlayerState::PLAYER_STATE_JUMP_ATTACK)
	{
		SetState(State::Active);
		meshComponent->SetVisible(true);
	}
	else
	{
		SetState(State::Disabling);
		meshComponent->SetVisible(false);
	}


	if (state == State::Active)
	{
		rotationAngle += Rotation;
		//Z軸を指定角度回転させる
		float radian = Math::ToRadians(rotationAngle);
		Quaternion rot = this->GetRotation();
		Quaternion inc(Vector3::UnitY, radian);
		Quaternion target = Quaternion::Concatenate(rot, inc);
		SetRotation(target);
	}

	position = ownerObject->GetPosition();
	position.z += 100.0f;
	SetPosition(position);
}

void JumpAttackPlayerObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	ownerObject->SetIsJumpAttackSuccess(true);
}
