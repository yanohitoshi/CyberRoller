#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

/*
@file ClearPointObject.h
@brief クリアポイントの生成と更新処理を行う
*/

class ClearPointObject :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	オブジェクト判別用tag
	*/
	ClearPointObject(const Vector3& _pos, const Tag& _objectTag);
	~ClearPointObject();

	/*
	@fn 更新処理
	@param	フレームレート固定用deltaTime
	*/
	void UpdateGameObject(float _deltaTime)override;


private:
	
	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;

	// 3Dモデルの描画を行うクラス
	MeshComponent* meshComponent;
	Mesh* mesh;

	// 当たり判定を行うクラス
	BoxCollider* boxCollider;
	// 回転させるときの角度
	float angle;
};

