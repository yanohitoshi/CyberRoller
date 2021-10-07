//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PushBoxObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"
#include "PushBoardObject.h"

/*
@fn コンストラクタ
@param	ポジション
@param	objectのサイズ
@param	オブジェクト判別用tag
@param  プッシュボードを更新するのに使用するデータ構造体
*/
PushBoxObject::PushBoxObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, PushBoxData _pushBoxData)
	: GameObject(false, _objectTag)
{
	//GameObjectメンバ変数の初期化
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	isPushBackToPlayer = true;
	isChackGroundToPlayer = true;

	// PushBoardとPushBoxの間隔
	float offsetX = 210.0f;
	float offsetY = 210.0f;
	float offsetZ = 100.0f;

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);

	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/groundModel/box.gpmesh"));

	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::GROUND_TAG, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());

	// 動く向きごとにPushBoardObjectの引数を変更して付与
	if (_pushBoxData.direction.x == 1.0f)
	{
		Vector3 boardSize = Vector3(50.0f, 200.0f, 200.0f);
		new PushBoardObject(Vector3(_p.x + offsetX, _p.y, _p.z + offsetZ), boardSize, PUSH_BOARD, _pushBoxData);
	}

	if (_pushBoxData.direction.x == -1.0f)
	{
		Vector3 boardSize = Vector3(50.0f, 200.0f, 200.0f);
		new PushBoardObject(Vector3(_p.x - offsetX, _p.y, _p.z + offsetZ), boardSize, PUSH_BOARD, _pushBoxData);
	}

	if (_pushBoxData.direction.y == 1.0f)
	{
		Vector3 boardSize = Vector3(200.0f, 50.0f, 200.0f);
		new PushBoardObject(Vector3(_p.x, _p.y + offsetY, _p.z + offsetZ), boardSize, PUSH_BOARD, _pushBoxData);
	}

	if (_pushBoxData.direction.y == -1.0f)
	{
		Vector3 boardSize = Vector3(200.0f, 50.0f, 200.0f);
		new PushBoardObject(Vector3(_p.x, _p.y - offsetY, _p.z + offsetZ), boardSize, PUSH_BOARD, _pushBoxData);
	}
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
PushBoxObject::~PushBoxObject()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void PushBoxObject::UpdateGameObject(float _deltaTime)
{
	//worldboxを渡す
	aabb = boxCollider->GetWorldBox();
}