#pragma once
#include "EnemyObjectBase.h"

class SphereCollider;

class TrackingEnemyObject :
    public EnemyObjectBase
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	再利用するかフラグ
	@param	オブジェクト判別用tag
	*/
	TrackingEnemyObject(const Vector3& _pos, const Tag _objectTag, float _moveSpeed,GameObject* _trackingObject);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~TrackingEnemyObject()override;

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn めり込み判定
	*/
	void FixCollision(AABB& myAABB, const AABB& pairAABB)override;

private:

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数(ジャンプ攻撃を行うエネミーとの判定を取る)
	@param	当たったGameObject
	*/
	void OnCollisionTracking(const GameObject& _hitObject);

	// 球体の当たり判定を行うクラス
	SphereCollider* trackingSphereCol;

public:

};

