#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateJumpAttackEnd.h
@brief ジャンプ攻撃終了からアイドリングに移行するまでを管理
*/
class PlayerObjectStateJumpAttackEnd :
    public PlayerObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	@param _owner 親クラスのポインタ
	*/
	PlayerObjectStateJumpAttackEnd(PlayerObject* _owner);

	/*
	@fn デストラクタ
	*/
	~PlayerObjectStateJumpAttackEnd()override;

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

	// ジャンプが行われているフレームを測るカウント変数
	int jumpFrameCount;
	// ジャンプが終了したかどうかのフラグ変数
	bool endFlag;

	// スイッチジャンプ時のジャンプ力の加速度
	const float SuccessJumpAccelPower;
	// スイッチジャンプ利用可能タイム
	const int SuccessJumpTime;
	// ジャンプアタック成功時の初速
	const float JumpAttackSuccessFirstPower;
};