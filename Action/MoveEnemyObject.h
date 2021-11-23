#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectBase.h"

/*
@file MoveEnemyObject.h
@brief 移動する敵オブジェクトクラス
*/
class MoveEnemyObject :
    public EnemyObjectBase
{
public:
	
	/*
	@fn コンストラクタ
	@param	ポジション
	@param	オブジェクト判別用tag
	@param	追跡対象のオブyジェクトのポインタ
	@param	左右に移動する敵が固有で持つデータ構造体
	*/
	MoveEnemyObject(const Vector3& _pos, const Tag _objectTag, MoveEnemyData _moveEnemyData);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~MoveEnemyObject()override;

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:

	/*
	@fn めり込み判定
	@param	自分のAABB
	@param	相手のAABB
	*/
	void FixCollision(AABB& myAABB, const AABB& pairAABB)override;

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;
};