#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ColliderComponent.h"
#include "PhysicsWorld.h"

/*
@file SphereCollider.h
@brief Sphereの当たり判定class
*/
class SphereCollider final : public ColliderComponent
{
public:

	/**
	@brief	コンストラクタ
	@param	アタッチするゲームオブジェクトのポインタ
	@param	他のオブジェクトと当たった時に呼ばれる関数ポインタ(GetOnCollisionFuncを呼ぶ)
	@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
	@param	当たり判定時に、めり込みから動かす処理の優先度を決める数値
	*/
	SphereCollider(GameObject* _owner, PhysicsTag tag, onCollisionFunc _func, int _updateOrder = 200, int _collisionOrder = 100);

	/**
	@brief	デストラクタ
	*/
	virtual ~SphereCollider();

	/**
	@brief	Transformのワールド変換
	*/
	virtual void OnUpdateWorldTransform() override;
	void refreshWorldTransform();


private:

	//オブジェクトに設定する用の球（中心をオブジェクトの中心にする）
	Sphere objectSphere;

	//当たり判定するときに使う球（中心をワールド座標の中心にする）
	Sphere worldSphere;

public: // ゲッターセッター

	/**
	@brief	当たり判定に使うSphereの設定
	@param	オブジェクトの大きさに合わせたSphereの構造体
	*/
	void SetObjectSphere(const Sphere& _sphere) { objectSphere = _sphere; }

	/**
	@brief	当たり判定時に使うワールド空間でのSphereを取得する
	@return 中心をワールド座標に合わせたSphereの構造体
	*/
	Sphere GetWorldSphere() const { return worldSphere; }

	//AABBのタグをとる
	PhysicsTag GetSphereTag() const { return mTag; }

};

