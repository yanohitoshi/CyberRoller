#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateRunTurn.h
@brief 走り状態からの切り替えしを管理
*/
class PlayerObjectStateRunTurn :
    public PlayerObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	PlayerObjectStateRunTurn();

	/*
	@fn デストラクタ
	*/
	~PlayerObjectStateRunTurn()override;

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
	@fn 入力チェック関数処理関数
	@param	_owner 親クラスのポインタ
	*/
	void ChackInputProcess(PlayerObject* _owner, const InputState& _keyState);

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

	// 減速力
	float decelerationForce;
	// ターン状態から走り状態に入る際の最低速度
	const float MinimumSpeed;

};

