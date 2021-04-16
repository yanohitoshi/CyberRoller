#pragma once
#include "PlayerObject.h"

class PlayerObject;
class SkeletalMeshComponent;

enum class PlayerState
{
	// 待機
	PLAYER_STATE_IDLE = 0,
	// 一定以上入力がなかった際の待機モーション
	PLAYER_STATE_IDLE_DANCE,
	// 走る
	PLAYER_STATE_RUN,
	// 走り状態開始
	PLAYER_STATE_RUN_START,
	// 走り状態停止
	PLAYER_STATE_RUN_STOP,
	// 走り状態から振り返り
	PLAYER_STATE_RUN_TURN,
	// 走り中壁に当たった際の怯み状態
	PLAYER_STATE_RUN_TO_FLINCH,
	// ジャンプループ
	PLAYER_STATE_JUMPLOOP, 
	// ジャンプスタート
	PLAYER_STATE_JUMPSTART,
	// ジャンプ終了から待機状態へ遷移
	PLAYER_STATE_JUMPEND_TO_IDLE,
	// ジャンプ終了から走り状態へ遷移
	PLAYER_STATE_JUMPEND_TO_RUN,
	// コンテニュー選択状態に入る前の状態
	PLAYER_STATE_DOWNSTART,
	// コンテニュー選択状態
	PLAYER_STATE_DOWN_LOOP,
	// コンテニュー状態
	PLAYER_STATE_DOWN_UP,
	// ゲームオーバー状態
	PLAYER_STATE_DOWN_OVER,
	// 死亡状態
	PLAYER_STATE_DEAD,
	// リスポーン状態
	PLAYER_STATE_RESPAWN,

	// 総アニメーション数
	PLAYER_STATE_NUM,
};

class PlayerObjectStateBase
{
public:
	
	/*
	@fn コンストラクタ
	*/
	PlayerObjectStateBase() {};

	/*
	@fn デストラクタ
	*/
	virtual ~PlayerObjectStateBase() {};

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return PlayerState　更新終了時のステータスを返す
	*/
	virtual PlayerState Update(PlayerObject* _owner, float _deltaTime) = 0;

	/*
	@fn インプット
	@brief	stateに応じて入力処理を行う
	@param	_owner 親クラスのポインタ
	@param	_keyState 入力情報
	*/
	virtual void Input(PlayerObject* _owner, const InputState& _keyState) {};
	
	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	virtual void Enter(PlayerObject* _owner, float _deltaTime) {};

protected:

	SkeletalMeshComponent* skeletalMeshComponent;
	PlayerState state;
	Vector3 velocity;
	float inputDeadSpace;
	const float MaxMoveSpeed = 1600.0f;

private:


};

