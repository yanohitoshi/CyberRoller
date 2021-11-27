//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "MoveWallBlock.h"
#include "SkeletalMeshComponent.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "RenderingObjectManager.h"
#include "Skeleton.h"
#include <string>
#include "BoxCollider.h"
#include "SandSmokeMakeManeger.h"
#include "MainCameraObject.h"
#include "FirstStageUI.h"
#include "PlayerObject.h"
#include "GeometryInstanceComponent.h"

/*
@fn コンストラクタ
@param	ポジション
@param	objectのサイズ
@param	オブジェクト判別用tag
@param	動く速度
@param	止まる位置
*/
MoveWallBlock::MoveWallBlock(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, float _speed, Vector3 _stopPos)
	: GameObject(false, _objectTag)
	, MoveSpeed(_speed)
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
	isPushBackToCamera = true;
	SetCheckSwitchTag(tag);

	// ジオメトリインスタンスコンポーネントを生成
	geometryInstanceComponent = new GeometryInstanceComponent(this, RENDERING_OBJECT_MANAGER->CreateMesh("Assets/Model/Environment/MoveWall/model/moveWallBox.gpmesh"), GeometryInstanceType::G_MOVE_WALL);
	// ジオメトリインスタンスマネージャークラスに追加
	geometryInstanceComponent->AddGeometryInstanceManager();

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::WALL_TAG, GetOnCollisionFunc());
	// 当たり判定のみY軸を大きくしたいので調整
	AABB aabb = { Vector3(-1.0f,-2.0f,-1.0f),Vector3(1.0f,2.0f,1.0f) };
	boxCollider->SetObjectBox(aabb);

	// 土煙エフェクトの付与
	new SandSmokeMakeManeger(this);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
MoveWallBlock::~MoveWallBlock()
{
	geometryInstanceComponent->RemoveGeometryInstanceManager();
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void MoveWallBlock::UpdateGameObject(float _deltaTime)
{
	// ワールドボックスの更新
	aabb = boxCollider->GetWorldBox();

	// 対象のスイッチの状態をチェック
	CheckSwitch(checkTag);

	// オープンフラグがtrueだったら
	if (openFlag == true)
	{
		OpenWall(_deltaTime);
	}

	// ポジションの更新
	SetPosition(position);
}

/*
@fn 壁を開く関数
@brief	壁を開く処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void MoveWallBlock::OpenWall(float _deltaTime)
{
	// 移動速度を付与
	velocity.z = MoveSpeed;
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

/*
@fn スイッチの状態を確認する関数
@param	どの種類のobjectか判定する用のTag
@param	フレームレート固定用deltaTime
*/
void MoveWallBlock::CheckSwitch(Tag& _tag)
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

/*
@fn どの壁がどのスイッチを確認するかセットする関数
@param	どの種類のobjectか判定する用のTag
*/
void MoveWallBlock::SetCheckSwitchTag(Tag& _tag)
{

	// なんの壁なのかを参照してチェックすべきスイッチをセット
	switch (_tag)
	{
		// 第一区画の壁だったら
	case(Tag::FIRST_MOVE_WALL):
		checkTag = Tag::FIRST_SWITCH;
		break;

		// 第二区画の壁だったら
	case(Tag::SECOND_MOVE_WALL):
		checkTag = Tag::SECOND_SWITCH;
		break;

		// ゲームクリア前の壁だったら
	case(Tag::CLEAR_SCENE_MOVE_WALL):
		checkTag = Tag::CLEAR_SCENE_SWITCH;
		break;
	}
}