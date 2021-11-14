#pragma once
#include "GameObject.h"

// クラスの前方宣言
class SphereCollider;
class EnemyObjectBase;

/*
@file PlayerTrackingArea.h
@brief プレイヤーを検知するスフィア判定クラス
*/
class PlayerTrackingArea :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	オブジェクト判別用tag
	@param	親となる敵クラスのポインタ
	@param	エリアの大きさとなる値
	*/
	PlayerTrackingArea(const Tag& _objectTag,EnemyObjectBase* _ownerEnemy,float _areaValue);

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
	@param	当たり判定タグ
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	// 当たり判定を行うクラス
	SphereCollider* sphereCollider;
	// 親となるクラスのポインタ
	EnemyObjectBase* owner;
};

