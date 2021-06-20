#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

// クラスの前方宣言
class SkeletalMeshComponent;

/*
@file PlayerObjectStateJumpLoop.h
@brief ジャンプループ状態を管理
*/
class PlayerObjectStateJumpLoop :
    public PlayerObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	PlayerObjectStateJumpLoop();

	/*
	@fn デストラクタ
	*/
	~PlayerObjectStateJumpLoop()override;

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
	@param	_keyState 入力情報
	@param	_axis 補正済みのアナログスティック情報
	*/
	void InputMovableProcess(PlayerObject* _owner, const InputState& _keyState, Vector3 _axis);

	/*
	@fn 入力がない場合の処理関数
	@param	_owner 親クラスのポインタ
	*/
	void UninputMovableProcess(PlayerObject* _owner);

	// ジャンプループが行われている時間を測るカウント変数
	int jumpLoopCount;
	// ジャンプスタートのアニメーションが終了するタイミングをずらすためのフラグ
	// ※見た目上ずらしたかったので作りました
	bool animChangeFlag;

	// 着地後回転モーションを含めるか判定する速度定数
	const float TurnValue;

	// ジャンプ中に移動速度を徐々に減らすための計算に使う補正値
	const float JumpCorrection;
	// スイッチジャンプ中に移動速度を徐々に減らすための計算に使う補正値
	const float SwitchJumpCorrection;
};

