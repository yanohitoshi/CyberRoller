#include "LightObject.h"
#include "Mesh.h"
#include <string>
#include "MeshComponent.h"
#include "Renderer.h"

LightObject::LightObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, bool _isRight)
	: GameObject(false, _objectTag)
{
	//GameObject�����o�ϐ��̏�����
	position = _p;
	position.x += 195.0f;
	position.z -= 110.0f;

	if (_isRight)
	{
		position.y += 50.0f;
	}
	else
	{
		position.y -= 200.0f;
	}

	SetPosition(position);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	//isPushBackToPlayer = true;
	//isChackGroundToPlayer = true;
	//isPushBackToCamera = true;
	//���f���`��p�̃R���|�[�l���g
	meshComponent = new MeshComponent(this, false, false);

	//Renderer�N���X����Mesh�ǂݍ��݊֐��𗘗p����Mesh���Z�b�g
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/light/PowerCells/SM_PowerCells_Floor.gpmesh"));
}

LightObject::~LightObject()
{
}

void LightObject::UpdateGameObject(float _deltaTime)
{
}
