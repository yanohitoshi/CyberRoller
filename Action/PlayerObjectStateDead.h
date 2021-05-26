#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObject;

class PlayerObjectStateDead :
    public PlayerObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	PlayerObjectStateDead();

	/*
	@fn デストラクタ
	*/
	~PlayerObjectStateDead()override;

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	PlayerState Update(PlayerObject* _owner, float _deltaTime)override;

	/*
	@fn インプット
	@brief	stateに応じて入力処理を行う
	@param	_owner 親クラスのポインタ
	@param	_keyState 入力情報
	*/
	void Input(PlayerObject* _owner, const InputState& _keyState)override;

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Enter(PlayerObject* _owner, float _deltaTime)override;

private:

	/*
	@fn 復帰遷移カウント処理関数
	*/
	void ToRespawnCountProcess(PlayerObject* _owner);

	// リスポーン状態に入るまでのカウントを測る変数
	int respawnCount;

	// リスポーン状態に入る時間
	const int respawnTime;
};

