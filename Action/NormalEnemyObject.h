#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectBase.h"

/*
@file NormalEnemyObject.h
@brief 動かない敵オブジェクトクラス
*/
class NormalEnemyObject :
    public EnemyObjectBase
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	オブジェクト判別用tag
	@param	追跡するオブジェクトのポインタ
	*/
	NormalEnemyObject(const Vector3& _pos, const Tag _objectTag, GameObject* _trackingObject);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~NormalEnemyObject()override;

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

	// 回転角度
	const float Angle;

public:

};

