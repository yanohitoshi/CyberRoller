#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class BoxCollider;
class FallExplosionObject;

/*
@file FallExplosionArea.h
@brief 落下開始するエリアオブジェクトクラス
*/
class FallExplosionArea:
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	オブジェクト判別用tag
	@param	エリアの広さ
	@param	爆発物の数
	*/
	FallExplosionArea(const Vector3& _pos, const Tag _objectTag, Vector3& _area, int _quantity);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~FallExplosionArea()override;

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

	// AABBの当たり判定を行うクラス
	BoxCollider* boxCollider;

	// 爆弾が降るエリア
	Vector3 area;

	// エリアに降る個数
	int quantity;

	bool isFallStart;

	std::vector<FallExplosionObject*> fallExplosionObjects;

public:

	bool GetIsFallStart() { return isFallStart; }

	Vector3 GetArea() { return area; }
};

