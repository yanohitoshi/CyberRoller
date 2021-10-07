//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "RespawnPoint.h"
#include "BoxCollider.h"

/*
@fn コンストラクタ
@param	ポジション
@param	当たり判定用AABB
@param	オブジェクト判別用tag
*/
RespawnPoint::RespawnPoint(const Vector3& _p, const AABB& _box, const Tag& _objectTag)
	: GameObject(false,_objectTag)
	, CorrectionPositionZ(600.0f)
{
	// ポジションの初期化
	position = _p;
	// 高さを補正
	position.z += CorrectionPositionZ;
	// ポジションをセット
	SetPosition(position);

	// 当たり判定用ボックスコライダー付与
	boxCollider = new BoxCollider(this,PhysicsTag::RESPOWN_TAG, GetOnCollisionFunc());
	boxCollider->SetObjectBox(_box);

}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
RespawnPoint::~RespawnPoint()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void RespawnPoint::UpdateGameObject(float _deltaTime)
{
}

/*
@fn 当たり判定が行われHitした際に呼ばれる関数
@param	当たったGameObject
@param	当たったGameObjectの当たり判定タグ
*/
void RespawnPoint::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
}