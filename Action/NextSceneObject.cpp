//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "NextSceneObject.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Mesh.h"
#include "PlayerObject.h"
#include "MainCameraObject.h"
#include "CrystalEffectManager.h"

/*
@fn コンストラクタ
@param	ポジション
@param	オブジェクト判別用tag
@param	プレイヤーのポインタ
@param	シーンの最後の動く壁オブジェクトのポインタ
*/
NextSceneObject::NextSceneObject(const Vector3& _pos, const Tag& _objectTag, PlayerObject* _playerObject, MoveWallBlock* _lastMoveWallBlock)
	: GameObject(false, _objectTag)
	, playerObject(_playerObject)
	, lastMoveWallBlock(_lastMoveWallBlock)
	, Angle(15.0f)
	, MoveSpeed(20.0f)
	, CalculationDrawEndPosition(3000.0f)
{

	//GameObjectメンバ変数の初期化
	SetPosition(_pos);
	SetScale(Vector3(50.0f, 50.0f, 50.0f));
	firstPos = _pos;
	tag = _objectTag;
	state = Active;
	velocity = Vector3(0.0f, 0.0f, 0.0f);

	//モデル描画用のコンポーネント
	meshComponent = new MeshComponent(this, false, false);
	//Rendererクラス内のMesh読み込み関数を利用してMeshをセット
	meshComponent->SetMesh(RENDERER->GetMesh("Assets/Model/Environment/goods_model/SM_Gems_01a.gpmesh"));
	//メッシュ情報取得
	mesh = meshComponent->GetMesh();
	// 輝度情報を取得
	luminance = mesh->GetLuminace();

	//当たり判定用のコンポーネント
	boxCollider = new BoxCollider(this, PhysicsTag::CLEAR_POINT_TAG, GetOnCollisionFunc());
	AABB aabb = { Vector3(-5.0f,-5.0f,-5.0f),Vector3(5.0f,5.0f,15.0f) };
	boxCollider->SetObjectBox(aabb);

	// 4色のエフェクトを付与
	new CrystalEffectManager(this,CrystalColor::WHITE, lastMoveWallBlock);
	new CrystalEffectManager(this, CrystalColor::RED, lastMoveWallBlock);
	new CrystalEffectManager(this, CrystalColor::BLUE, lastMoveWallBlock);
	new CrystalEffectManager(this, CrystalColor::GREEN, lastMoveWallBlock);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
NextSceneObject::~NextSceneObject()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void NextSceneObject::UpdateGameObject(float _deltaTime)
{
	if (playerObject->GetClearFlag() == true)
	{
		// 速度付与
		velocity.z = MoveSpeed;
		
		// 回転処理
		RotationProcess();

		// 可動処理
		MovableProcess();

		// カメラに注視させるのでポジションを渡す
		mainCamera->SetLerpObjectPos(position);
	}
}

/*
@fn 回転処理関数
*/
void NextSceneObject::RotationProcess()
{
	//Z軸を指定角度回転させる
	float radian = Math::ToRadians(Angle);
	Quaternion rot = this->GetRotation();
	Quaternion inc(Vector3::UnitZ, radian);
	Quaternion target = Quaternion::Concatenate(rot, inc);
	SetRotation(target);

}

/*
@fn 可動処理関数
*/
void NextSceneObject::MovableProcess()
{
	// ポジションに速度を足す
	position += velocity;
	// ポジションを更新
	SetPosition(position);

	// 定位置まで届いたら描画カット
	if (position.z >= firstPos.z + CalculationDrawEndPosition)
	{
		meshComponent->SetVisible(false);
	}

}

/*
@fn 当たり判定が行われHitした際に呼ばれる関数
@param	当たったGameObject
@param	当たったGameObjectの当たり判定タグ
*/
void NextSceneObject::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
}