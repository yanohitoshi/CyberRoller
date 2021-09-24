//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PushBoardObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"

PushBoardObject::PushBoardObject(GameObject* _owner,const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Vector3& _distance, const Vector3& _direction, const float& _speed, const float& _cutBackSpeed ,MoveDirectionTag _moveTag) :
	GameObject(false, _objectTag)
	, MoveSpeed(_speed)
	, CutBackSpeed(_cutBackSpeed)
{
	//GameObjectメンバ変数の初期化
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	initPos = _p;
	goalPos = initPos + _distance;
	direction = _direction;
	moveTag = _moveTag;
	inversionFlag = false;
	isSendVelocityToPlayer = true;

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);

	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/groundModel/box.gpmesh"));

	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::MOVE_GROUND_TAG, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());
}

PushBoardObject::~PushBoardObject()
{
}

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

void PushBoardObject::ChackInversionProcess()
{
	//前後移動用判定
	if (moveTag == MoveDirectionTag::MOVE_X)
	{
		// X軸の処理
		ChackAxisX();
		// 現在の仕様上1つの軸移動しか行わないため返す
		return;
	}

	//左右移動用判定
	if (moveTag == MoveDirectionTag::MOVE_Y)
	{
		// Y軸の処理
		ChackAxisY();
		// 現在の仕様上1つの軸移動しか行わないため返す
		return;
	}

	//上下移動用判定
	if (moveTag == MoveDirectionTag::MOVE_Z)
	{
		// Z軸の処理
		ChackAxisZ();
		// 現在の仕様上1つの軸移動しか行わないため返す
		return;
	}



}

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
