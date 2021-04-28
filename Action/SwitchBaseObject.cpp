#include "SwitchBaseObject.h"
#include "MeshComponent.h"
#include "SwitchBlock.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "SwitchBlock.h"
#include "Mesh.h"

SwitchBaseObject::SwitchBaseObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Tag& _switchTag)
	: GameObject(false, _objectTag)
{
	// ポジション・スケール・Tagの初期化
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);

	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/switch_model/S_EnergySwitch.gpmesh"));
	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();

	// 当たり判定用ボックスコライダーを付与
	boxCollider = new BoxCollider(this, ColliderComponent::SWITCH_BASE, GetOnCollisionFunc());
	// 当たり判定用AABBを作成
	AABB aabb = { Vector3(-75.0f,-75.0f,-150.0f),Vector3(75.0f,75.0f,40.0f) };
	// 作成したAABBをセット
	boxCollider->SetObjectBox(aabb);

	// スイッチ本体を付与
	new SwitchBlock(this, Vector3(2.6f,2.6f,2.0f), _switchTag);
}

SwitchBaseObject::~SwitchBaseObject()
{
}

void SwitchBaseObject::UpdateGameObject(float _deltaTime)
{
	// ワールド空間のAABBを更新
	aabb = boxCollider->GetWorldBox();
	// ポジションに速度を足す
	position = position + velocity * _deltaTime;
	// ポジションの更新
	SetPosition(position);

}

void SwitchBaseObject::OnCollision(const GameObject& _hitObject)
{
	// ヒットしたオブジェクトが動く床だったら
	if (_hitObject.GetTag() == Tag::MOVE_GROUND)
	{
		// 動く床の持つ速度を付与
		velocity = _hitObject.GetVelocity();
	}
}
