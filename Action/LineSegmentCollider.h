#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PhysicsWorld.h"
#include "ColliderComponent.h"

class MainCameraObject;

/*
 @file LineSegmentCollider.h
 @brief 線分の当たり判定クラス（未実装）
*/
class LineSegmentCollider : public ColliderComponent
{
public:

	/*
	@brief	コンストラクタ
	@param	アタッチするゲームオブジェクトのポインタ
	@param	他のオブジェクトと当たった時に呼ばれる関数ポインタ(GetOnCollisionFuncを呼ぶ)
	@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
	@param	当たり判定時に、めり込みから動かす処理の優先度を決める数値
	*/
	LineSegmentCollider(GameObject* _owner, ColliderComponent::PhysicsTag tag,onCollisionFunc _func, int _updateOrder = 200, int _collisionOrder = 100);

	/*
	@brief	デストラクタ
	*/
	virtual ~LineSegmentCollider();

	/*
	@brief	Transformのワールド変換
	*/
	void OnUpdateWorldTransform() override;


private:

	//オブジェクトに設定する用の線分（中心をオブジェクトの中心にする）
	LineSegment objectLineSegment;

	//当たり判定するときに使う線分（中心をワールド座標の中心にする）
	LineSegment worldLineSegment;

	// 値
	float value;

	// 当たった場所
	float contactPoint;

	// 前方ベクトル
	Vector3 forwardVec;

	// hitした間隔
	float interval;

	// 衝突した場所
	Vector3 hitPoint;

	// 衝突した場所
	Vector3 point;

	// 使用するカメラのポインタ
	MainCameraObject* mainCamera;

public: // ゲッターセッター

	/*
	@brief	当たり判定に使う線分の設定
	@param	オブジェクトの大きさに合わせた線分の構造体
	*/
	void SetObjectLineSegment(const LineSegment& _lineSegment) { objectLineSegment = _lineSegment; }
	
	/*
	@brief	値(線分の長さ)をセットする関数(いらないかもしれないです…)
	@param	_value セットする値
	*/
	void Setvalue(const float& _value) { value = _value; }
	
	/*
	@brief	前方ベクトルをセットする関数
	@param	_forward セットする前方ベクトル
	*/
	void SetforwardVector(const Vector3& _forward) { forwardVec = _forward; }

	/*
	@brief	当たり判定時に使うワールド空間での線分Vectorを取得する
	@return 中心をワールド座標に合わせた線分Vector
	*/
	LineSegment GetWorldLineSegment() const { return worldLineSegment; }
	
	/*
	@brief	当たった場所を得るgetter
	@return 当たった場所の情報(float)
	*/
	float GetContactPoint(){ return contactPoint; }

	/*
	@brief	線分の間隔をセットする関数
	@param	_interval セットする線分の間隔(float)
	*/
	void SetInterval(const float& _interval) { interval = _interval; }
	
	/*
	@brief	線分の間隔を得るgetter
	@return 線分の間隔の情報(float)
	*/
	float GetInterval() const { return interval; }
	
	/*
	@brief	当たった場所をセットする関数
	@param	_interval セットする当たった場所(Vector3)
	*/
	void SetHitPointVector(const Vector3& _hitPoint) { hitPoint = _hitPoint; }
	
	/*
	@brief	当たった場所を得るgetter(Vector3)
	@return 当たった場所の情報(Vector3)
	*/
	Vector3 GetHitPointVector()const { return hitPoint; }

};

