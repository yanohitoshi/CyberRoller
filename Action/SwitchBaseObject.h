#pragma once
#include "GameObject.h"

class BoxCollider;
class Mesh;
class MeshComponent;

class SwitchBaseObject :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	objectのサイズ
	@param	オブジェクト判別用tag
	@param  どの区画のスイッチなのかを判別させるようのTag
	*/
	SwitchBaseObject(const Vector3& _p, const Vector3& _size, const Tag& _objectTag, const Tag& _switchTag);
	~SwitchBaseObject();
	
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
	BoxCollider* boxCollider;
	// 当たり判定を行うクラス
	Mesh* mesh;


};

