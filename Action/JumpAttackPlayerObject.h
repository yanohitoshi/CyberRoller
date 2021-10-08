#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class MeshComponent;
class PlayerObject;
class SphereCollider;
class BoxCollider;

/*
@file JumpAttackPlayerObject.h
@brief ジャンプ攻撃時のプレイヤーオブジェクト
*/
class JumpAttackPlayerObject :
    public GameObject
{
public:
	
	/*
	@fn コンストラクタ
	@param	ポジション
	@param	オブジェクトのサイズ
	@param	オブジェクト判別用tag
	*/
	JumpAttackPlayerObject(PlayerObject* _ownerObject, const Vector3& _size, const Tag _objectTag);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~JumpAttackPlayerObject();

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;

	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	@param	当たったGameObjectの当たり判定タグ
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

private:

	// 3Dモデルの描画を行うクラス
    MeshComponent* meshComponent;
	// 親となるオブジェクトのポインタ
	PlayerObject* ownerObject;
	// AABBの当たり判定を行うクラス
	BoxCollider* boxCollider;
	// 球体の当たり判定を行うクラス
	SphereCollider* sphereCollider;

	// 回転する際の角度
	float rotationAngle;
	// 回転角に足し続ける値定数
	const float Rotation;
	// Z軸をずらすための定数
	const float ShiftPositionZ;
};

