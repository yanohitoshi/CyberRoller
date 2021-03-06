#pragma once
#include "GameObject.h"

class BoxCollider;

class RespawnPoint :
    public GameObject
{
public:
	
	/*
	@fn コンストラクタ
	@param	ポジション
	@param	当たり判定用AABB
	@param	オブジェクト判別用tag
	*/
	RespawnPoint(const Vector3& _p, const AABB& _box, const Tag& _objectTag);
	~RespawnPoint();
	
	/*
	@fn 更新処理
	@param	フレームレート固定用deltaTime
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;
	// 当たり判定を行うクラス
	BoxCollider* boxCollider;
	// リスポーンするかどうかフラグ
	bool reSpownFlag;
};

