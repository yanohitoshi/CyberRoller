#pragma once

#include "PhysicsWorld.h"
#include "ColliderComponent.h"



/*
 @file LineSegmentCollider.h
 @brief 線分の当たり判定クラス（未実装）
*/

class LineSegmentCollider : public ColliderComponent
{
public:
	/**
	@brief	コンストラクタ
	@param	アタッチするゲームオブジェクトのポインタ
	@param	他のオブジェクトと当たった時に呼ばれる関数ポインタ(GetOnCollisionFuncを呼ぶ)
	@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
	@param	当たり判定時に、めり込みから動かす処理の優先度を決める数値
	*/
	LineSegmentCollider(GameObject* _owner, ColliderComponent::PhysicsTag tag,onCollisionFunc _func, int _updateOrder = 200, int _collisionOrder = 100);

	/**
	@brief	デストラクタ
	*/
	virtual ~LineSegmentCollider();

	/**
	@brief	Transformのワールド変換
	*/
	void OnUpdateWorldTransform() override;

	/**
	@brief	当たり判定に使う線分の設定
	@param	オブジェクトの大きさに合わせた線分の構造体
	*/
	void SetObjectLineSegment(const LineSegment& _lineSegment) { objectLineSegment = _lineSegment; }
	void Setvalue(const float& _value) { value = _value; }
	void SetforwardVector(const Vector3& _forward) { forwardVec = _forward; }

	/**
	@brief	当たり判定時に使うワールド空間での線分Vectorを取得する
	@return 中心をワールド座標に合わせた線分Vector
	*/
	LineSegment GetWorldLineSegment() const { return worldLineSegment; }
	float GetContactPoint(){ return contactPoint; }
	float contactPoint;
private:

	//オブジェクトに設定する用の線分（中心をオブジェクトの中心にする）
	LineSegment objectLineSegment;

	//当たり判定するときに使う線分（中心をワールド座標の中心にする）
	LineSegment worldLineSegment;

	float value;

	// 前方ベクトル
	Vector3 forwardVec;

};

