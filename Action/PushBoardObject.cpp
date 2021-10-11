//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PushBoardObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"
#include "PushBoxObject.h"
#include "GeometryInstanceComponent.h"

/*
@fn コンストラクタ
@param	ポジション
@param	objectのサイズ
@param	オブジェクト判別用tag
@param  プッシュボードを更新するのに使用するデータ構造体
*/
PushBoardObject::PushBoardObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, PushBoxData _pushBoxData)
	:GameObject(false, _objectTag)
	, MoveSpeed(_pushBoxData.speed)
	, CutBackSpeed(_pushBoxData.cutBackSpeed)
{
	//GameObjectメンバ変数の初期化
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	initPos = _p;
	goalPos = initPos + _pushBoxData.distance;
	direction = _pushBoxData.direction;
	moveTag = _pushBoxData.tag;
	inversionFlag = false;
	isSendVelocityToPlayer = true;
	isPushBackToPlayer = true;

	////モデル描画用のコンポーネント
	//meshComponent = new MeshComponent(this, false, false);
	////Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	//meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/groundModel/box.gpmesh"));
	geometryInstanceComponent = new GeometryInstanceComponent(this, RENDERER->GetMesh("Assets/Model/Environment/groundModel/lightGround.gpmesh"), GeometryInstanceType::G_PUDH_BOARD, 500);
	geometryInstanceComponent->AddGeometryInstanceManager();
	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = geometryInstanceComponent->GetMesh();

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::MOVE_GROUND_TAG, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
PushBoardObject::~PushBoardObject()
{
	geometryInstanceComponent->RemoveGeometryInstanceManager();
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void PushBoardObject::UpdateGameObject(float _deltaTime)
{
	//worldboxを渡す
	aabb = boxCollider->GetWorldBox();

	// 可動処理
	MovableProcess();

	// 反転するかチェック
	ChackInversionProcess();

	// ポジションに速度を足す
	position = position + velocity * _deltaTime;

	// ポジションを更新
	SetPosition(position);
}

/*
@fn 反転チェック処理関数
*/
void PushBoardObject::ChackInversionProcess()
{
	// 動く方向のタグを見て処理を変える
	switch (moveTag)
	{
	case MOVE_X:
		// X軸の処理
		ChackAxisX();
		break;
	case MOVE_Y:
		// Y軸の処理
		ChackAxisY();
		break;
	case MOVE_Z:
		// Z軸の処理
		ChackAxisZ();
		break;
	}
}

/*
@fn 可動処理関数
*/
void PushBoardObject::MovableProcess()
{
	// 速度を反転するかどうかを判定
	if (inversionFlag == false)
	{
		// 向きに速度を掛ける
		velocity = direction * MoveSpeed;
	}
	else if (inversionFlag == true)
	{
		// 戻る際は減速を掛ける
		velocity = direction * (MoveSpeed * CutBackSpeed) * -1.0f;
	}
}

/*
@fn X軸反転チェック処理関数
*/
void PushBoardObject::ChackAxisX()
{
	// 到達点に達していたら反転
	if (position.x >= goalPos.x && direction.x == 1.0f || position.x <= goalPos.x && direction.x == -1.0f)
	{
		inversionFlag = true;
	}

	// 元の位置に達していたら反転
	if (position.x <= initPos.x && direction.x == 1.0f || position.x >= initPos.x && direction.x == -1.0f)
	{
		inversionFlag = false;
	}
}

/*
@fn Y軸反転チェック処理関数
*/
void PushBoardObject::ChackAxisY()
{
	// 到達点に達していたら反転
	if (position.y >= goalPos.y && direction.y == 1.0f || position.y <= goalPos.y && direction.y == -1.0f)
	{
		inversionFlag = true;
	}

	// 元の位置に達していたら反転
	if (position.y <= initPos.y && direction.y == 1.0f || position.y >= initPos.y && direction.y == -1.0f)
	{
		inversionFlag = false;
	}
}

/*
@fn Z軸反転チェック処理関数
*/
void PushBoardObject::ChackAxisZ()
{
	// 到達点に達していたら反転
	if (position.z >= goalPos.z && direction.z == 1.0f || position.z <= goalPos.z && direction.z == -1.0f)
	{
		inversionFlag = true;
	}

	// 元の位置に達していたら反転
	if (position.z <= initPos.z && direction.z == 1.0f || position.z >= initPos.z && direction.z == -1.0f)
	{
		inversionFlag = false;
	}
}