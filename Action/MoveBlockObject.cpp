//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "MoveBlockObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include <string>
#include "Renderer.h"
#include "BoxCollider.h"

MoveBlockObject::MoveBlockObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag,const Vector3& _distance, const Vector3& _direction, const float& _speed, MoveDirectionTag _moveTag) :
	GameObject(false, _objectTag)
{
	//GameObjectメンバ変数の初期化
	SetPosition(_p);
	SetScale(_size);
	tag = _objectTag;
	state = Active;
	initPos = _p;
	goalPos = initPos + _distance;
	direction = _direction;
	moveSpeed = _speed;
	moveTag = _moveTag;
	inversionFlag = false;
	isPushBackToPlayer = true;
	isSendVelocityToPlayer = true;
	isChackGroundToPlayer = true;

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/groundModel/box.gpmesh"));
	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, ColliderComponent::MOVE_GROUND_TAG, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());

}

MoveBlockObject::~MoveBlockObject()
{
}

void MoveBlockObject::UpdateGameObject(float _deltaTime)
{
	//worldboxを渡す
	aabb = boxCollider->GetWorldBox();

	// 可動処理
	MovableProcess();

	// 移動状態確認
	ChackInversionProcess();

	// ポジションに速度を足す
	position = position + velocity * _deltaTime;

	// ポジションを更新
	SetPosition(position);

}

void MoveBlockObject::MovableProcess()
{
	// 反転するかどうかフラグを判定しそれに応じて速度を付与
	if (inversionFlag == false)
	{
		// 通常の速度を代入
		velocity = direction * moveSpeed;
	}
	else if (inversionFlag == true)
	{
		// 反転した速度を代入
		velocity = direction * moveSpeed * -1.0f;
	}
}

void MoveBlockObject::ChackInversionProcess()
{
	// 動く向きのTagごとに反転する条件を見て反転判定
	if (moveTag == MoveDirectionTag::MOVE_X)
	{
		// X軸の処理
		ChackAxisX();
		// 現在の仕様上1つの軸移動しか行わないため返す
		return;
	}

	if (moveTag == MoveDirectionTag::MOVE_Y)
	{
		// Y軸の処理
		ChackAxisY();
		// 現在の仕様上1つの軸移動しか行わないため返す
		return;
	}

	if (moveTag == MoveDirectionTag::MOVE_Z)
	{
		// Z軸の処理
		ChackAxisZ();
		// 現在の仕様上1つの軸移動しか行わないため返す
		return;
	}
}

void MoveBlockObject::ChackAxisX()
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

void MoveBlockObject::ChackAxisY()
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

void MoveBlockObject::ChackAxisZ()
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
