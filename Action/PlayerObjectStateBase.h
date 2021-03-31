#pragma once
#include "PlayerObject.h"

class PlayerObject;

enum class PlayerState
{
	// 待機
	PLAYER_STATE_IDLE = 0,
	// ジャンプ終了
	PLAYER_STATE_WALK,
	// 走る
	PLAYER_STATE_RUN,
	// ジャンプループ
	PLAYER_STATE_JUMPLOOP, 
	// ジャンプスタート
	PLAYER_STATE_JUMPSTART,
	// ジャンプ終了
	PLAYER_STATE_JUMPEND,
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
	PlayerObjectStateBase() {}

	/*
	@fn デストラクタ
	*/
	virtual ~PlayerObjectStateBase() {};

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
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
	@fn コンストラクタ
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	virtual void Enter(PlayerObject* _owner, float _deltaTime) {};

protected:

	//PlayerObject* owner;
	PlayerState state;
	Vector3 velocity;

};

