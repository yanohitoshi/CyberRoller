//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ExplosionArea.h"
#include "ExplosionObjectBase.h"
#include "SphereCollider.h"

/*
@fn コンストラクタ
@param	ポジション
@param	親クラスのポインタ
*/
ExplosionArea::ExplosionArea(const Tag& _objectTag, ExplosionObjectBase* _owner)
	:GameObject(false, _objectTag)
	, owner(_owner)
	, ExplosionAreaSize(300.0f)
{
	// 初期化
	SetState(State::Active);
	SetPosition(owner->GetPosition());

	//ジャンプ攻撃判定用のsphereCollider
	sphereCollider = new SphereCollider(this, PhysicsTag::EXPLOSION_AREA_TAG, GetOnCollisionFunc());
	Sphere sphere = { Vector3(0.0f,0.0f,0.0f),ExplosionAreaSize };
	sphereCollider->SetObjectSphere(sphere);
}

/*
@fn デストラクタ
@brief  objectの削除を行う
*/
ExplosionArea::~ExplosionArea()
{
}

/*
@fn アップデート関数
@brief	更新処理を行う
@param	_deltaTime 前のフレームでかかった時間
*/
void ExplosionArea::UpdateGameObject(float _deltaTime)
{
	// ポジション更新
	SetPosition(owner->GetPosition());

	// 親が爆発状態か判定
	isActive = owner->GetIsExplode();
	if (isActive)
	{
		SetState(State::Active);
	}
	else
	{
		SetState(State::Disabling);
	}
}

/*
@fn 当たり判定が行われHitした際に呼ばれる関数
@param	当たったGameObject
@param	当たり判定タグ
*/
void ExplosionArea::OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)
{
}