//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "NeedlePanelObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "RenderingObjectManager.h"
#include "BoxCollider.h"
#include "NeedleObject.h"
#include "GeometryInstanceComponent.h"

/*
@fn コンストラクタ
@param	ポジション
@param	objectのサイズ
@param	オブジェクト判別用tag
*/
NeedlePanelObject::NeedlePanelObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag) :
	GameObject(false, _objectTag)
{
	//GameObjectメンバ変数の初期化
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;

	// ジオメトリインスタンスコンポーネントを生成
	geometryInstanceComponent = new GeometryInstanceComponent(this, RENDERING_OBJECT_MANAGER->CreateMesh("Assets/Model/Environment/Ground/model/lightGround.gpmesh"), GeometryInstanceType::G_NEEDLE_PANEL);
	// ジオメトリインスタンスマネージャークラスに追加
	geometryInstanceComponent->AddGeometryInstanceManager();
	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::NEEDLE_TAG, GetOnCollisionFunc());
	AABB box = { Vector3(-0.8f,-0.8f,-1.0f),Vector3(0.8f,0.8f,8.0f) };
	boxCollider->SetObjectBox(box);

	new NeedleObject(this, Vector3(0.0f, 0.0f, 50.0f), Vector3(2.5f, 2.5f, 2.0f), Tag::NEEDLE);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
NeedlePanelObject::~NeedlePanelObject()
{
	geometryInstanceComponent->RemoveGeometryInstanceManager();
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void NeedlePanelObject::UpdateGameObject(float _deltaTime)
{
	//worldboxを渡す
	aabb = boxCollider->GetWorldBox();
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
void NeedlePanelObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// ヒットしたオブジェクトが動く床だったら
	if (_hitObject.GetTag() == Tag::MOVE_GROUND)
	{
		// 動く床の速度を付与
		velocity = _hitObject.GetVelocity();
	}
}
