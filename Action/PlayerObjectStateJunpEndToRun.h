#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

// クラスの前方宣言
class SkeletalMeshComponent;

/*
@file PlayerObjectStateJunpEndToRun.h
@brief ジャンプ終了から走り状態に移行するまでを管理
*/
class PlayerObjectStateJunpEndToRun :
    public PlayerObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	PlayerObjectStateJunpEndToRun();

	/*
	@fn デストラクタ
	*/
	~PlayerObjectStateJunpEndToRun()override;

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
	@fn 入力チェック関数処理関数
	@param	_owner 親クラスのポインタ
	@param	_keyState 入力情報
	*/
	void CheckInputProcess(PlayerObject* _owner, const InputState& _keyState);

	/*
	@fn 入力がある場合の処理関数
	@param	_owner 親クラスのポインタ
	@param	_axis 補正済みのアナログスティック情報
	*/
	void InputMovableProcess(PlayerObject* _owner, Vector3 _axis);

	/*
	@fn 入力がない場合の処理関数
	@param	_owner 親クラスのポインタ
	*/
	void UninputMovableProcess(PlayerObject* _owner);
	
	/*
	@fn ジャンプ状態に遷移するための準備処理関数
	@param	_owner 親クラスのポインタ
	*/
	void JumpTransitionProcess(PlayerObject* _owner);

	// 非移動入力時の減速力
	const float UnInputDecelerationForce;
	// 移動入力時の減速力
	const float InputDecelerationForce;

};