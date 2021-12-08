//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "JumpSwitchObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "RenderingObjectManager.h"
#include "BoxCollider.h"
#include "GeometryInstanceComponent.h"

/*
@fn コンストラクタ
@param	ポジション
@param	objectのサイズ
@param	オブジェクト判別用tag
*/
JumpSwitchObject::JumpSwitchObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag)
	: GameObject(false, _objectTag)
{
	//GameObjectメンバ変数の初期化
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;

	// ジオメトリインスタンスコンポーネントを生成
	geometryInstanceComponent = new GeometryInstanceComponent(this, RENDERING_OBJECT_MANAGER->CreateMesh("Assets/Model/Environment/JumpSwitch/model/jumpSwitch.gpmesh"), GeometryInstanceType::G_JUMP_SWITCH);
	// ジオメトリインスタンスマネージャークラスに追加
	geometryInstanceComponent->AddGeometryInstanceManager();

	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = geometryInstanceComponent->GetMesh();
	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::JUMP_SWITCH_TAG, GetOnCollisionFunc());
	AABB aabb = { mesh->GetBox() };
	aabb.min.z -= 5.0f;
	boxCollider->SetObjectBox(aabb);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
JumpSwitchObject::~JumpSwitchObject()
{
	geometryInstanceComponent->RemoveGeometryInstanceManager();
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void JumpSwitchObject::UpdateGameObject(float _deltaTime)
{
	// ポジションに速度を足す
	position = position + velocity * _deltaTime;
	// ポジションを更新
	SetPosition(position);
}

/*
@fn 当たり判定が行われHitした際に呼ばれる関数
@param	当たったGameObject
@param	当たったGameObjectの当たり判定タグ
*/
void JumpSwitchObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// ヒットしたオブジェクトが動く床だったら
	if (_hitObject.GetTag() == Tag::MOVE_GROUND)
	{
		// 動く床の持つ速度を付与
		velocity = _hitObject.GetVelocity();
	}
}