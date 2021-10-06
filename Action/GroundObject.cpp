//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GroundObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"

GroundObject::GroundObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, bool _isLight)
	: GameObject(false, _objectTag)
{
	//GameObjectメンバ変数の初期化
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	isPushBackToPlayer = true;
	isChackGroundToPlayer = true;
	isPushBackToCamera = true;
	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this,false,false);

	if (_isLight)
	{
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/groundModel/lightGround.gpmesh"));
	}
	else
	{
		//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
		meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/groundModel/normalGround.gpmesh"));
	}

	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this,PhysicsTag::GROUND_TAG, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());

}

GroundObject::~GroundObject()
{
}

void GroundObject::UpdateGameObject(float _deltaTime)
{
	//worldboxを渡す
	aabb = boxCollider->GetWorldBox();
}
