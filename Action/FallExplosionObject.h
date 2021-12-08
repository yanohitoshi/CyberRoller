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
class FallExplosionArea;
enum class ExplosionObjectState;

/*
@file FallExplosionObject.h
@brief 落下する爆発物オブジェクト
*/
class FallExplosionObject :
    public ExplosionObjectBase
{
public:

	/*
	@fn コンストラクタ
	@param	親クラスのポインタ
	@param	ポジション
	@param	オブジェクト判別用tag
	*/
	FallExplosionObject(FallExplosionArea* _owner, const Vector3& _pos, const Tag _objectTag);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~FallExplosionObject()override;

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

	// オーナーとなる爆発物落下エリアクラスのポインタ変数
	FallExplosionArea* owner;

};