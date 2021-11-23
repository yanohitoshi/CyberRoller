#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateIdlingDance.h
@brief ダンス状態を管理
*/
class PlayerObjectStateIdlingDance :
    public PlayerObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	PlayerObjectStateIdlingDance();

	/*
	@fn デストラクタ
	*/
	~PlayerObjectStateIdlingDance()override;

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

	/*
	@fn isDancingのgetter関数
	@return	static bool ダンス中かどうかのフラグ変数
	*/
	static bool GetIsDancing() { return isDancing; }

private:

	// ダンス状態かどうかを表すフラグ変数
	static bool isDancing;
};

