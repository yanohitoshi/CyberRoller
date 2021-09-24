#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class MeshComponent;
class BoxCollider;
class Mesh;
class PlayerObject;
class MoveWallBlock;

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
	ClearPointObject(const Vector3& _pos, const Tag& _objectTag, PlayerObject* _playerObject, MoveWallBlock* _lastMoveWallBlock);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~ClearPointObject();

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime)override;


private:
	
	/*
	@fn 回転処理関数
	*/
	void RotationProcess();

	/*
	@fn 可動処理関数
	*/
	void MovableProcess();
	/*
	@fn 当たり判定が行われHitした際に呼ばれる関数
	@param	当たったGameObject
	*/
	void OnCollision(const GameObject& _hitObject, const PhysicsTag _physicsTag)override;

	// 3Dモデルの描画を行うクラス
	MeshComponent* meshComponent;
	Mesh* mesh;

	PlayerObject* playerObject;
	MoveWallBlock* lastMoveWallBlock;
	// 当たり判定を行うクラス
	BoxCollider* boxCollider;
	// 回転する際の角度
	const float Angle;
	// 移動速度の定数
	const float MoveSpeed;
};

