//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerTrackingArea.h"
#include "EnemyObjectStateBase.h"
#include "TrackingEnemyObject.h"
#include "SphereCollider.h"

/*
@fn コンストラクタ
@param	オブジェクト判別用tag
@param	親となる敵クラスのポインタ
@param	エリアの大きさとなる値
*/
PlayerTrackingArea::PlayerTrackingArea(const Tag& _objectTag, EnemyObjectBase* _ownerEnemy, float _areaValue)
	:GameObject(false, _objectTag)
	, owner(_ownerEnemy)
{
	SetPosition(owner->GetPosition());

	//ジャンプ攻撃判定用のsphereCollider
	sphereCollider = new SphereCollider(this, PhysicsTag::PLAYER_TRACKING_AREA_TAG, GetOnCollisionFunc());
	Sphere sphere = { Vector3(0.0f,0.0f,0.0f),_areaValue };
	sphereCollider->SetObjectSphere(sphere);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
PlayerTrackingArea::~PlayerTrackingArea()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void PlayerTrackingArea::UpdateGameObject(float _deltaTime)
{
	// ポジションを固定
	SetPosition(position);
}

/*
@fn 当たり判定が行われHitした際に呼ばれる関数
@param	当たったGameObject
@param	当たり判定タグ
*/
void PlayerTrackingArea::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// リスポーン状態だったら返す
	if (owner->GetNowState() == EnemyState::ENEMY_STATE_RESPAWN)
	{
		return;
	}

	// プレイヤーを見つけたら
	if (_hitObject.GetTag() == Tag::PLAYER)
	{
		// 親クラスを追跡状態にセット
		owner->SetIsTracking(true);
		// 追跡する対象のポジションをセット
		owner->SetAttackObjectPosition(_hitObject.GetPosition());
	}
}
