#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class Mesh;

class NeedlePanelObject :
    public GameObject
{
public:
	
	/*
	@fn コンストラクタ
	@param	ポジション
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	*/
	NeedlePanelObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag);
	~NeedlePanelObject();
	
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
	Mesh* mesh;
	MeshComponent* meshComponent;
	// 当たり判定を行うクラス
	BoxCollider* boxCollider;

};

