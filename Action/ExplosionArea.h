#pragma once
#include "GameObject.h"

// クラスの前方宣言
class SphereCollider;
class ExplosionObject;

class ExplosionArea :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	親クラスのポインタ
	*/
	ExplosionArea(const Tag& _objectTag, ExplosionObject* _owner);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~ExplosionArea();

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

	// 当たり判定を行うクラス
	SphereCollider* sphereCollider;
	// 親となるクラスのポインタ
	ExplosionObject* owner;

	bool isActive;
	// 攻撃エリアのサイズ
	const float ExplosionAreaSize;
};

