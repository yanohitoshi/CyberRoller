#include "LightObject.h"
#include "Mesh.h"
#include <string>
#include "MeshComponent.h"
#include "Renderer.h"

LightObject::LightObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, bool _isRight)
	: GameObject(false, _objectTag)
{
	//GameObjectメンバ変数の初期化
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
	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);

	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/light/PowerCells/SM_PowerCells_Floor.gpmesh"));
}

LightObject::~LightObject()
{
}

void LightObject::UpdateGameObject(float _deltaTime)
{
}
