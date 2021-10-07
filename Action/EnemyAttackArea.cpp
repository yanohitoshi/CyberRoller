//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"
#include "EnemyAttackArea.h"
#include "EnemyObjectBase.h"
#include "SphereCollider.h"

/*
@fn コンストラクタ
@param	ポジション
@param	親クラスのポインタ
*/
EnemyAttackArea::EnemyAttackArea(const Tag& _objectTag, EnemyObjectBase* _ownerEnemy)
	:GameObject(false, _objectTag)
	, ownerEnemy(_ownerEnemy)
	, AttackArea(50.0f)
	, EnableTime(60)
{
	SetPosition(ownerEnemy->GetPosition());
	isEnable = true;
	disableCount = 0;

	//ジャンプ攻撃判定用のsphereCollider
	sphereCollider = new SphereCollider(this, PhysicsTag::ENEMY_ATTACK_AREA_TAG, GetOnCollisionFunc());
	Sphere sphere = { Vector3(0.0f,0.0f,0.0f),AttackArea };
	sphereCollider->SetObjectSphere(sphere);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
EnemyAttackArea::~EnemyAttackArea()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void EnemyAttackArea::UpdateGameObject(float _deltaTime)
{
	// ポジションを更新
	SetPosition(ownerEnemy->GetPosition());

	// 無効状態になっていたら
	if (!isEnable)
	{
		// 無効時間を数える
		++disableCount;
		// 有効時間に到達したら
		if (disableCount > EnableTime)
		{
			// 有効状態にする
			isEnable = true;
		}
	}
}

/*
@fn 当たり判定が行われHitした際に呼ばれる関数
@param	当たったGameObject
@param	当たり判定タグ
*/
void EnemyAttackArea::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
	// リスポーン状態だったら返す
	if (ownerEnemy->GetNowState() == EnemyState::ENEMY_STATE_RESPAWN)
	{
		return;
	}

	// プレイヤーを見つけたら
	if (_hitObject.GetTag() == Tag::PLAYER && _physicsTag == PhysicsTag::PLAYER_TAG && isEnable)
	{
		// 親クラスを攻撃状態にセット
		ownerEnemy->SetIsAttack(true);
		isEnable = false;
		disableCount = 0;
	}
}
