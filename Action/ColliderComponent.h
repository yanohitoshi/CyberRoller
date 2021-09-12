#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Component.h"
#include "Collision.h"

// クラスの前方宣言
class GameObject;

/*
@file ColliderComponent.h
@brief ColliderComponent系派生classの基底のクラス
*/
class ColliderComponent : public Component
{
public:
//===================== publicのメンバ関数 ======================//

	/*
	 @enum  PhysicsTag
			PhysicsWorld内でどのObjectなのか判別するタグ
	*/
	enum PhysicsTag
	{
		GROUND_TAG,
		MOVE_GROUND_TAG,
		WALL_TAG,
		PLAYER_TAG,
		SWITCH_TAG,
		SWITCH_BASE,
		JUMP_SWITCH_TAG,
		GROUND_CHECK_TAG,
		FOOT_CHECK_TAG,
		SWITCH_CHECK_TAG,
		CAMERA_TAG,
		CLEAR_POINT_TAG,
		NEEDLE_TAG,
		RESPOWN_TAG,
		NORMAL_ENEMY_TAG,
		ATTACK_RANGE_TAG
	};

    /*
	@brief	コンストラクタ
	@param	アタッチするゲームオブジェクトのポインタ
	@param	なんのColliderなのか判定用Tag(PhysicsTag)
    @param	コンポーネントの更新順番（数値が小さいほど早く更新される）
    @param  当たり判定時に、めり込みから動かす処理の優先度を決める数値
    */
	ColliderComponent(GameObject* _owner, PhysicsTag tag, int _updateOrder = 200,int _collisionOrder = 100);


private:

	bool isTrigger;			//実体を伴う当たり判定をするかどうか
	int	 collisionOrder;	//数値が大きい方を優先してめり込みから動かす処理をする（0以下は動かさない)

protected:

	// 当たり判定を行うかどうかの判定用Tag
	PhysicsTag mTag;

public: // ゲッターセッター
	
	/**
	@brief	めり込み動かす際の優先度を示す数値を取得する
	@return 優先度を示す数値(int)
	*/
	int GetCollisionOrder() const { return collisionOrder; }

};

