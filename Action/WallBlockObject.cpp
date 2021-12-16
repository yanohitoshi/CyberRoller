//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "WallBlockObject.h"
#include "SkeletalMeshComponent.h"
#include "MeshComponent.h"
#include "MainCameraObject.h"
#include <string>
#include "Skeleton.h"
#include "BoxCollider.h"
#include  "Mesh.h"

/*
@fn コンストラクタ
@param	ポジション
@param	objectのサイズ
@param	オブジェクト判別用tag
*/
WallBlockObject::WallBlockObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag) :
	GameObject(false, _objectTag)
{
	//GameObjectメンバ変数の初期化
	SetPosition(Vector3(_p));
	SetScale(_size);
	tag = _objectTag;
	isPushBackToPlayer = true;
	isPushBackToCamera = true;

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this,false,false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(GRAPHICS_RESOURCE->CreateMesh("Assets/Model/Environment/wall_model/wallBox.gpmesh"));

	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this,PhysicsTag::WALL_TAG,GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());

}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
WallBlockObject::~WallBlockObject()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void WallBlockObject::UpdateGameObject(float _deltaTime)
{
	// ワールドボックスの更新
	aabb = boxCollider->GetWorldBox();
}