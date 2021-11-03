#include "BreakBlockObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "BreakBlockObjectEffectManager.h"

BreakBlockObject::BreakBlockObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag)
	: GameObject(false, _objectTag)
	, CorrectionAabbValue(0.1f)
{
	//GameObjectメンバ変数の初期化
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	isPushBackToPlayer = true;
	isCheckGroundToPlayer = true;
	isPushBackToCamera = true;

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/groundModel/lightGround.gpmesh"));
	//メッシュ情報取得
	mesh = meshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::BREAK_GROUND_TAG, GetOnCollisionFunc());
	aabb = mesh->GetBox();

	//プレイヤーがすり抜けないようにAABBのサイズを補正
	aabb.max.y += CorrectionAabbValue;
	aabb.min.y -= CorrectionAabbValue;
	boxCollider->SetObjectBox(aabb);

	new BreakBlockObjectEffectManager(this);
}

BreakBlockObject::~BreakBlockObject()
{
}

void BreakBlockObject::UpdateGameObject(float _deltaTime)
{
	//worldboxを渡す
	aabb = boxCollider->GetWorldBox();
}

void BreakBlockObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	if (_physicsTag == PhysicsTag::EXPLOSION_AREA_TAG)
	{
		meshComponent->SetVisible(false);
		SetState(State::Disabling);
	}
}
