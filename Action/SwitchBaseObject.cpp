//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "SwitchBaseObject.h"
#include "MeshComponent.h"
#include "SwitchBlock.h"
#include "BoxCollider.h"
#include "SwitchBlock.h"
#include "ResultSwitchObject.h"
#include "Mesh.h"
#include "GeometryInstanceComponent.h"

/*
@fn コンストラクタ
@param	ポジション
@param	objectのサイズ
@param	オブジェクト判別用tag
@param  どの区画のスイッチなのかを判別させるようのTag
@param	チュートリアル用Switchかどうかのフラグ
*/
SwitchBaseObject::SwitchBaseObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Tag& _switchTag , bool _isTutorial)
	: GameObject(false, _objectTag)
	, Angle(90.0f)
{
	// ポジション・スケール・Tagの初期化
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	//isPushBackToPlayer = true;
	isCheckGroundToPlayer = true;

	// ジオメトリインスタンスコンポーネントを生成
	geometryInstanceComponent = new GeometryInstanceComponent(this, GRAPHICS_RESOURCE->CreateMesh("Assets/Model/Environment/Switch/model/S_EnergySwitch.gpmesh"), GeometryInstanceType::G_BASE_SWITCH);
	// ジオメトリインスタンスマネージャークラスに追加
	geometryInstanceComponent->AddGeometryInstanceManager();

	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = geometryInstanceComponent->GetMesh();

	// 当たり判定用ボックスコライダーを付与
	boxCollider = new BoxCollider(this, PhysicsTag::SWITCH_BASE_TAG, GetOnCollisionFunc());
	// 当たり判定用AABBを作成
	AABB aabb = { Vector3(-75.0f,-75.0f,-150.0f),Vector3(75.0f,75.0f,40.0f) };
	// 作成したAABBをセット
	boxCollider->SetObjectBox(aabb);

	// スイッチ本体を付与
	new SwitchBlock(this, Vector3(2.6f,2.6f,2.0f), _switchTag, _isTutorial);
	
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
SwitchBaseObject::~SwitchBaseObject()
{
	geometryInstanceComponent->RemoveGeometryInstanceManager();
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void SwitchBaseObject::UpdateGameObject(float _deltaTime)
{
	// ワールド空間のAABBを更新
	aabb = boxCollider->GetWorldBox();
	// ポジションに速度を足す
	position = position + velocity * _deltaTime;
	// ポジションの更新
	SetPosition(position);
}

/*
@fn 当たり判定が行われHitした際に呼ばれる関数
@param	当たったGameObject
@param	当たったGameObjectの当たり判定タグ
*/
void SwitchBaseObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// ヒットしたオブジェクトが動く床だったら
	if (_hitObject.GetTag() == Tag::MOVE_GROUND)
	{
		// 動く床の持つ速度を付与
		velocity = _hitObject.GetVelocity();
	}
}