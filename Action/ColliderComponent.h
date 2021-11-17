#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Component.h"
#include "Collision.h"

// クラスの前方宣言
class GameObject;

/*
@enum  PhysicsTag PhysicsWorld内でどのObjectなのか判別するタグ
*/
enum class PhysicsTag
{
	// 地面
	GROUND_TAG,
	// 動く地面
	MOVE_GROUND_TAG,
	// 壊れる地面
	BREAK_GROUND_TAG,
	// 壁
	WALL_TAG,
	// プレイヤー
	PLAYER_TAG,
	// ジャンプ攻撃中のプレイヤー
	JUMP_ATTACK_PLAYER_TAG,
	// スイッチ
	SWITCH_TAG,
	// スイッチの土台
	SWITCH_BASE_TAG,
	// ジャンプスイッチ
	JUMP_SWITCH_TAG,
	// 収集物
	COLLECTION_TAG,
	// 接地判定
	GROUND_CHECK_TAG,
	// 足元チェック
	FOOT_CHECK_TAG,
	// カメラ
	CAMERA_TAG,
	// クリア地点
	CLEAR_POINT_TAG,
	// 棘
	NEEDLE_TAG,
	// 爆弾
	BOMB_TAG,
	FALL_BOMB_TAG,
	FALL_BOMB_AREA_TAG,
	// リスポーンポイント
	RESPOWN_TAG,
	// 敵
	ENEMY_TAG,
	// プレイヤーの攻撃エリア
	ATTACK_RANGE_TAG,
	// プレイヤーを敵が追跡するエリア
	PLAYER_TRACKING_AREA_TAG,
	// 敵の攻撃判定エリア
	ENEMY_ATTACK_AREA_TAG,
	// 爆発判定エリア
	EXPLOSION_AREA_TAG,
	// カメラモードをbehindカメラにするエリア判定
	CAMERA_MODE_CHANGE_AREA,

};

/*
@file ColliderComponent.h
@brief ColliderComponent系派生classの基底のクラス
*/
class ColliderComponent : public Component
{
public:
//===================== publicのメンバ関数 ======================//

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
	
	/*
	@brief	めり込み動かす際の優先度を示す数値を取得する
	@return 優先度を示す数値(int)
	*/
	int GetCollisionOrder() const { return collisionOrder; }

};

