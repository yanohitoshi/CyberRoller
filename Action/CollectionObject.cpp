//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CollectionObject.h"
#include "MeshComponent.h"
#include "RenderingObjectManager.h"
#include "BoxCollider.h"
#include "Mesh.h"
#include "CollectionEffectManager.h"
#include "CrystalEffectManager.h"
#include "CollectionUI.h"

/*
@fn コンストラクタ
@param	ポジション
@param	オブジェクト判別用tag
@param	何番目の収集物かを判定するタグ
*/
CollectionObject::CollectionObject(const Vector3& _pos, const Tag& _objectTag, CollectionTag _collectionTag)
	: GameObject(false, _objectTag)
	, ShiftPositionZ(100.0f)
	, CollectedSpeed(1200.0f)
	, VerticalMoveSpeed(50.0f)
	, ChangeRateTime(30)
	, CollectedMoveTime(15)
	, CollectedVisibleTime(60)
{
	//GameObjectメンバ変数の初期化
	velocity.Zero;
	position = _pos;
	position.z += ShiftPositionZ;
	SetPosition(position);
	SetScale(Vector3(25.0f, 25.0f, 25.0f));
	collectionTag = _collectionTag;
	value = 0.0f;
	rate = 0.0f;
	frameCount = 0;
	collectedRotationAngle = 0.0f;
	collectedCount = 0;
	isCollected = false;

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERING_OBJECT_MANAGER->CreateMesh("Assets/Model/Environment/Collection/model/SM_Small_Gems.gpmesh"));
	
	//メッシュ情報取得
	mesh = meshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::COLLECTION_TAG, GetOnCollisionFunc());
	AABB aabb = { Vector3(-5.0f,-5.0f,-5.0f),Vector3(5.0f,5.0f,15.0f) };
	boxCollider->SetObjectBox(aabb);

	new CollectionEffectManager(this);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
CollectionObject::~CollectionObject()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void CollectionObject::UpdateGameObject(float _deltaTime)
{
	// 描画されてなかったらreturn
	if (!meshComponent->GetVisible())
	{
		return;
	}

	// AABBを更新
	aabb = boxCollider->GetWorldBox();

	// 収集されていたら
	if (isCollected)
	{
		// 収集されている時の関数を呼び出す
		Collected(_deltaTime);
	}
	else
	{
		// それ以外の時の移動処理
		Movable(_deltaTime);
	}
}

/*
@fn 回転処理関数
@param 回転する角度
@param 回転する軸
*/
void CollectionObject::RotationProcess(float _angle, Vector3 _axis)
{
	//_axis軸を_angle度回転させる
	float radian = Math::ToRadians(_angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(_axis, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);
}

/*
@fn 可動処理関数
@param	_deltaTime 前のフレームでかかった時間
*/
void CollectionObject::Movable(float _deltaTime)
{
	// フレームカウントを数える
	++frameCount;

	// レートを変更する時間が来たら計算しなおす
	if (frameCount % ChangeRateTime == 0)
	{
		++value;
		rate = Math::Cos(value);
	}

	// レートに速度を掛ける
	velocity.z = rate * VerticalMoveSpeed;

	// ポジション更新
	SetPosition(position + velocity * _deltaTime);
}

/*
@fn 収集された時の処理関数
@param	_deltaTime 前のフレームでかかった時間
*/
void CollectionObject::Collected(float _deltaTime)
{
	// 収集されてからのカウントを数える
	++collectedCount;
	// 回転角に1足す
	++collectedRotationAngle;
	// 回転処理
	RotationProcess(collectedRotationAngle, Vector3::UnitZ);

	// 収集された後移動する時間まで移動する
	if (collectedCount <= CollectedMoveTime)
	{
		velocity.z = CollectedSpeed;
		SetPosition(position + velocity * _deltaTime);
	}

	// 時間が来たら描画を切る
	if (collectedCount >= CollectedVisibleTime)
	{
		meshComponent->SetVisible(false);
	}
}

/*
@fn 当たり判定が行われHitした際に呼ばれる関数
@param	当たったGameObject
@param	当たったGameObjectの当たり判定タグ
*/
void CollectionObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// プレイヤーもしくはジャンプアタックプレイヤーに当たったら
	if (_physicsTag == PhysicsTag::PLAYER_TAG || _physicsTag == PhysicsTag::JUMP_ATTACK_PLAYER_TAG)
	{
		// 収集状態にする
		isCollected = true;
	}
}