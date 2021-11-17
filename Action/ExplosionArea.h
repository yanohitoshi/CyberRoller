#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SphereCollider;
class ExplosionObjectBase;

/*
@file ExplosionArea.h
@brief 爆破効果範囲を管理するクラス
*/
class ExplosionArea :
    public GameObject
{
public:

	/*
	@fn コンストラクタ
	@param	ポジション
	@param	親クラスのポインタ
	*/
	ExplosionArea(const Tag& _objectTag, ExplosionObjectBase* _owner);

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
	ExplosionObjectBase* owner;

	bool isActive;
	// 攻撃エリアのサイズ
	const float ExplosionAreaSize;
};

