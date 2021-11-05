#include "CollectionObject.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Mesh.h"
#include "CollectionEffectManager.h"
#include "CrystalEffectManager.h"
#include "CollectionUI.h"

CollectionObject::CollectionObject(const Vector3& _pos, const Tag& _objectTag, CollectionTag _collectionTag)
	: GameObject(false, _objectTag)
	, ShiftPositionZ(100.0f)
	, CollectedSpeed(1200.0f)
	, VerticalMoveSpeed(50.0f)
{
	//GameObjectメンバ変数の初期化
	velocity.Zero;
	position = _pos;
	position.z += ShiftPositionZ;
	SetPosition(position);
	SetScale(Vector3(25.0f, 25.0f, 25.0f));

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/goods_model/SM_Small_Gems.gpmesh"));
	
	//メッシュ情報取得
	mesh = meshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::COLLECTION_TAG, GetOnCollisionFunc());
	AABB aabb = { Vector3(-5.0f,-5.0f,-5.0f),Vector3(5.0f,5.0f,15.0f) };
	boxCollider->SetObjectBox(aabb);

	collectionTag = _collectionTag;
	value = 0.0f;
	rate = 0.0f;
	frameCount = 0;
	collectedRotationAngle = 0.0f;
	collectedCount = 0;
	isCollected = false;

	new CollectionEffectManager(this);
}

CollectionObject::~CollectionObject()
{
}

void CollectionObject::UpdateGameObject(float _deltaTime)
{

	if (!meshComponent->GetVisible())
	{
		return;
	}

	aabb = boxCollider->GetWorldBox();

	if (isCollected)
	{
		Collected(_deltaTime);
	}
	else
	{
		Movable(_deltaTime);
	}
}

void CollectionObject::RotationProcess(float _angle, Vector3 _axis)
{
	//_axis軸を_angle度回転させる
	float radian = Math::ToRadians(_angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

void CollectionObject::Movable(float _deltaTime)
{
	++frameCount;
	if (frameCount % 30 == 0)
	{
		++value;
		rate = Math::Cos(value);
	}

	velocity.z = rate * VerticalMoveSpeed;

	SetPosition(position + velocity * _deltaTime);
}

void CollectionObject::Collected(float _deltaTime)
{
	++collectedCount;
	++collectedRotationAngle;
	RotationProcess(collectedRotationAngle, Vector3::UnitZ);

	if (collectedCount <= 15)
	{
		velocity.z = CollectedSpeed;
		SetPosition(position + velocity * _deltaTime);
	}

	if (collectedCount >= 60)
	{
		meshComponent->SetVisible(false);
	}
}

void CollectionObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	if (_physicsTag == PhysicsTag::PLAYER_TAG || _physicsTag == PhysicsTag::JUMP_ATTACK_PLAYER_TAG)
	{
		isCollected = true;
	}
}