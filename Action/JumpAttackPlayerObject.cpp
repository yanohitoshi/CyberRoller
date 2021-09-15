#include "JumpAttackPlayerObject.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "PlayerObject.h"

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
}

JumpAttackPlayerObject::~JumpAttackPlayerObject()
{
}

void JumpAttackPlayerObject::UpdateGameObject(float _deltaTime)
{

	if (ownerObject->GetNowState() == PlayerState::PLAYER_STATE_JUMP_ATTACK)
	{
		meshComponent->SetVisible(true);
	}
	else
	{
		meshComponent->SetVisible(false);
	}

	position = ownerObject->GetPosition();
	position.z += 100.0f;
	SetPosition(position);
}
