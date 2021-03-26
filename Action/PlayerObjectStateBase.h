#pragma once
#include "PlayerObject.h"

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
	// 総アニメーション数
	PLAYER_STATE_NUM,
};

class PlayerObjectStateBase
{
public:
	
	/*
	@fn コンストラクタ
	*/
	PlayerObjectStateBase(PlayerObject* _owner) { owner = _owner; }

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
	virtual PlayerState Update(float _deltaTime) {};

	/*
	@fn インプット
	@brief	stateに応じて入力処理を行う
	@param	_owner 親クラスのポインタ
	@param	_keyState 入力情報
	*/
	virtual void Input(const InputState& _keyState) {};
	
	/*
	@fn コンストラクタ
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	virtual void Enter(float _deltaTime) {};

protected:

	PlayerObject* owner;
	PlayerState state;
	Vector3 velocity;

};

