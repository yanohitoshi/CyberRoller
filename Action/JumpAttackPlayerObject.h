#pragma once
#include "GameObject.h"

class MeshComponent;
class PlayerObject;
class SphereCollider;

class JumpAttackPlayerObject :
    public GameObject
{
public:
	
	/*
	@fn コンストラクタ
	@param	ポジション
	@param	再利用するかフラグ
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
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

private:

    MeshComponent* meshComponent;
	PlayerObject* ownerObject;
	SphereCollider* sphereCollider;

	// 回転する際の角度
	float rotationAngle;
	// 回転角に足し続ける値定数
	const float Rotation;
	State tmpState;

};

