#pragma once
#include "PlayerObject.h"

class PlayerObject;

enum class PlayerState
{
	// 待機
	PLAYER_STATE_IDLE = 0,
	// 走る
	PLAYER_STATE_RUN,
	// ジャンプスタート
	PLAYER_STATE_JUMPSTART,
	// ジャンプループ
	PLAYER_STATE_JUMPLOOP, 
	// ジャンプ終了
	PLAYER_STATE_JUMPEND,
	// ジャンプ終了
	PLAYER_STATE_WALK,
	// ジャンプ終了
	PLAYER_STATE_DOWN,
	// ジャンプ終了
	PLAYER_STATE_DOWN_LOOP,
	// ジャンプ終了
	PLAYER_STATE_DOWN_UP,
	// ジャンプ終了
	PLAYER_STATE_DOWN_OVER,
	// ジャンプ終了
	PLAYER_STATE_PLAYER_DEAD,

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

