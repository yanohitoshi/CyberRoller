#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateIdle.h
@brief アイドリング状態を管理
*/
class PlayerObjectStateIdle :
    public PlayerObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	PlayerObjectStateIdle();

	/*
	@fn デストラクタ
	*/
	~PlayerObjectStateIdle()override;

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return PlayerState　更新終了時のステータスを返す
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
	@fn 入力チェック処理関数
	@param	_owner 親クラスのポインタ
	*/
	void CheckMovableInputProcess(PlayerObject* _owner);

	/*
	@fn ダンス開始カウント関数
	@brief	ダンス開始までのカウントを数え時間が来たらフラグを切り替える
	*/
	void DanceCountProcess();

	// ダンス状態に切り替えるフラグ変数
	bool isDanceFlag;
	// 入力が無い間カウントを数える用のカウント変数
	int danceCount;
	// ダンスを開始する時間
	const int DanceStartTime;
};