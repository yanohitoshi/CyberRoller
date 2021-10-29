//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GroundObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"
#include "GeometryInstanceComponent.h"

/*
@fn コンストラクタ
@param	ポジション
@param	objectのサイズ
@param	オブジェクト判別用tag
@param	ライト付か否か
*/
GroundObject::GroundObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag)
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

	// ジオメトリインスタンスコンポーネントを生成
	geometryInstanceComponent = new GeometryInstanceComponent(this, RENDERER->GetMesh("Assets/Model/Environment/groundModel/normalGround.gpmesh"), GeometryInstanceType::G_GROUND,1500);
	// ジオメトリインスタンスマネージャークラスに追加
	geometryInstanceComponent->AddGeometryInstanceManager();

	//メッシュ情報取得
	mesh = geometryInstanceComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this,PhysicsTag::GROUND_TAG, GetOnCollisionFunc());
	aabb = mesh->GetBox();

	//プレイヤーがすり抜けないようにAABBのサイズを補正
	aabb.max.y += CorrectionAabbValue;
	aabb.min.y -= CorrectionAabbValue;
	boxCollider->SetObjectBox(aabb);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
GroundObject::~GroundObject()
{
	geometryInstanceComponent->RemoveGeometryInstanceManager();
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void GroundObject::UpdateGameObject(float _deltaTime)
{
	//worldboxを渡す
	aabb = boxCollider->GetWorldBox();
}