#pragma once
#include "GameObject.h"

class SphereCollider;
class TrackingEnemyObject;

class PlayerTrackingArea :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	*/
	PlayerTrackingArea(const Tag& _objectTag,TrackingEnemyObject* _ownerEnemy);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~PlayerTrackingArea();

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	// 当たり判定を行うクラス
	SphereCollider* sphereCollider;
	TrackingEnemyObject* ownerEnemy;
};

