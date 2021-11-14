#pragma once
#include "EnemyObjectBase.h"

// クラスの前方宣言
class SphereCollider;
class Mesh;

/*
@file EnhancedEnemyObject.h
@brief ジャンプ攻撃で死なない強化された敵オブジェクトクラス
*/
class EnhancedEnemyObject :
    public EnemyObjectBase
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	オブジェクト判別用tag
	@param	移動速度
	@param	追跡するオブジェクトのポインタ
	@param	追跡エリアの値
	*/
	EnhancedEnemyObject(const Vector3& _pos, const Tag _objectTag, float _moveSpeed, float _areaValue);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~EnhancedEnemyObject()override;

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn めり込み判定
	@param	自分のAABB
	@param	相手のAABB
	*/
	void FixCollision(AABB& myAABB, const AABB& pairAABB)override;

private:

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	@param	当たり判定タグ
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	// Meshの読み込みを行うクラス
	Mesh* mesh;

	// 回転角度
	const float Angle;

public:
};

