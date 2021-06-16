#include "MoveWallBlock.h"
#include "SkeletalMeshComponent.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Skeleton.h"
#include <string>
#include "BoxCollider.h"
#include "SandSmokeMakeManeger.h"
#include "MainCameraObject.h"
#include "FirstStageUI.h"
#include "PlayerObject.h"


MoveWallBlock::MoveWallBlock(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, float _speed, Vector3 _stopPos)
	: GameObject(false, _objectTag)
	, moveSpeed(_speed)
	, stopPos(_stopPos)
	, ShiftPositionY(200.0f)
{
	//GameObjectメンバ変数の初期化
	position = Vector3(_p.x , _p.y - ShiftPositionY, _p.z);
	SetPosition(position);
	scale = _size;
	SetScale(scale);
	tag = _objectTag;
	velocity = Vector3(0.0f, 0.0f, 0.0f);
	openFlag = false;
	isPushBackToPlayer = true;
	isFlinchToPlayer = true;
	isPushBackToCamera = true;
	SetChackSwitchTag(tag);

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this,false,false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/moveWall_model/moveWallBox.gpmesh"));

	//メッシュからAABBで使うx,y,zのminとmaxを取得する
	mesh = new Mesh();
	mesh = meshComponent->GetMesh();
	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, ColliderComponent::WALL_TAG, GetOnCollisionFunc());
	boxCollider->SetObjectBox(mesh->GetBox());

	// 土煙エフェクトの付与
	new SandSmokeMakeManeger(this);

}

MoveWallBlock::~MoveWallBlock()
{
}


void MoveWallBlock::UpdateGameObject(float _deltaTime)
{
	// ワールドボックスの更新
	aabb = boxCollider->GetWorldBox();

	// 対象のスイッチの状態をチェック
	ChackSwitch(chackTag);

	// オープンフラグがtrueだったら
	if (openFlag == true)
	{
		OpenWall(_deltaTime);
	}

	// ポジションの更新
	SetPosition(position);
}

void MoveWallBlock::OpenWall(float _deltaTime)
{
	// 移動速度を付与
	velocity.z = moveSpeed;
	// ポジション変更
	position.z -= velocity.z * _deltaTime;

	// 止まるべき位置に来たら停止
	if (position.z <= stopPos.z)
	{
		// オープンフラグをfalseに
		openFlag = false;
		// 速度を0.0fに
		velocity.z = 0.0f;
	}
}

void MoveWallBlock::ChackSwitch(Tag& _tag)
{
	// チェック用可変長配列
	std::vector<GameObject*> switches;
	// 対象となるスイッチの可変長配列を探す
	switches = GameObject::FindGameObject(_tag);
	// 存在するスイッチとONになっているスイッチを数えるためのカウント初期化
	int switchCount = 0;
	int flagCount = 0;

	// 可変長配列内のスイッチをチェック
	for (auto itr : switches)
	{
		// 存在数を数える
		++switchCount;
		// スイッチがONの状態だったら
		if (itr->GetSwitchFlag() == true)
		{
			// ONの数を数える
			++flagCount;
		}
	}

	// 存在するスイッチの数とONになっているスイッチの数が同じだったら
	if (flagCount == switchCount)
	{
		// オープンフラグをtrueに
		openFlag = true;
	}
}

void MoveWallBlock::SetChackSwitchTag(Tag& _tag)
{

	// なんの壁なのかを参照してチェックすべきスイッチをセット
	switch (_tag)
	{
		// 第一区画の壁だったら
	case(Tag::FIRST_MOVE_WALL):
		chackTag = Tag::FIRST_SWITCH;
		break;

		// 第二区画の壁だったら
	case(Tag::SECOND_MOVE_WALL):
		chackTag = Tag::SECOND_SWITCH;
		break;

		// ゲームクリア前の壁だったら
	case(Tag::CLEAR_SCENE_MOVE_WALL):
		chackTag = Tag::CLEAR_SCENE_SWITCH;
		break;
	}
}


