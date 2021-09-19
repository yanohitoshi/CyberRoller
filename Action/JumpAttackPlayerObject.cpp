#include "JumpAttackPlayerObject.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "SphereCollider.h"

JumpAttackPlayerObject::JumpAttackPlayerObject(PlayerObject* _ownerObject, const Vector3& _size, const Tag _objectTag)
	: GameObject(false, _objectTag)
{
	ownerObject = _ownerObject;
	position = ownerObject->GetPosition();
	position.z += 100.0f;
	SetPosition(position);
	SetScale(_size);

	meshComponent = new MeshComponent(this, false, false);
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/CannonBall/CannonBall.gpmesh"));

	//Ú’n”»’è—p‚ÌsphereCollider
	sphereCollider = new SphereCollider(this, ColliderComponent::JUMP_ATTACK_PLAYER_TAG, GetOnCollisionFunc());
	Sphere jumpAttackSphere = { Vector3(0.0f,0.0f,0.0f),3.0f };
	sphereCollider->SetObjectSphere(jumpAttackSphere);

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

	position = ownerObject->GetPosition();
	position.z += 100.0f;
	SetPosition(position);
}

void JumpAttackPlayerObject::OnCollision(const GameObject& _hitObject)
{
	ownerObject->SetIsJumpAttackSuccess(true);
}
