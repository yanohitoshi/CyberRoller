#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ExplosionObjectBase.h"

// クラスの前方宣言
class MeshComponent;
class Mesh;
class BoxCollider;
class ExplosionObjectStateBase;
enum class ExplosionObjectState;

/*
@file ExplosionObject.h
@brief 爆発するオブジェクトクラス
*/
class ExplosionObject :
    public ExplosionObjectBase
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	オブジェクト判別用tag
	*/
	ExplosionObject(const Vector3& _pos, const Tag _objectTag);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~ExplosionObject()override;

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

	// Z軸をずらす定数
	const float ShiftPositionZ;

public:


};

