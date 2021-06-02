#pragma once
#include "GameObject.h"

// クラスの前置宣言
class BoxCollider;

class LightPositionChangePoint :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	当たり判定用AABB
	@param	オブジェクト判別用tag
	*/
	LightPositionChangePoint(const Vector3& _p, const AABB& _box, const Tag& _objectTag);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~LightPositionChangePoint();

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
	void OnCollision(const GameObject& _hitObject)override;
	// 当たり判定を行うクラス
	BoxCollider* boxCollider;
	// リスポーンポイントとなるかどうかフラグ
	bool reSpownFlag;

	const float ShiftPositionZ;
};

