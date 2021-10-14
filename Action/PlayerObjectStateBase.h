#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObject.h"

// クラスの前方宣言
class PlayerObject;
class SkeletalMeshComponent;

/*
@enum　PlayerState
プレイヤーのステータス判別用
*/
enum class PlayerState
{
	// 待機
	PLAYER_STATE_IDLE = 0,
	// 一定以上入力がなかった際の待機モーション
	PLAYER_STATE_IDLE_DANCE,
	// 走る
	PLAYER_STATE_RUN,
	// 走り状態開始
	PLAYER_STATE_RUN_START,
	// 走り状態停止
	PLAYER_STATE_RUN_STOP,
	// 走り状態から振り返り
	PLAYER_STATE_RUN_TURN,
	// 走り中壁に当たった際の怯み状態
	PLAYER_STATE_KNOCKBACK,
	// ジャンプループ
	PLAYER_STATE_JUMPLOOP, 
	// ジャンプスタート
	PLAYER_STATE_JUMPSTART,
	// ジャンプ終了から待機状態へ遷移
	PLAYER_STATE_JUMPEND_TO_IDLE,
	// ジャンプ終了から走り状態へ遷移
	PLAYER_STATE_JUMPEND_TO_RUN,
	// ジャンプ攻撃状態	
	PLAYER_STATE_JUMP_ATTACK,
	// ジャンプ攻撃終了状態
	PLAYER_STATE_JUMP_ATTACK_END,
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
	// 落下死亡状態
	PLAYER_STATE_FALL_DEAD,
	// リスポーン状態
	PLAYER_STATE_RESPAWN,

	// 総アニメーション数
	PLAYER_STATE_NUM,
};

/*
@file PlayerObjectStateBase.h
@brief プレイヤーのステートパターンの基底クラス
*/
class PlayerObjectStateBase
{
public:
	
	/*
	@fn コンストラクタ
	*/
	PlayerObjectStateBase()
		: MaxFallSpeed(-2000.0f)
		, MaxMoveSpeed(1800.0f)
	{};

	/*
	@fn デストラクタ
	*/
	virtual ~PlayerObjectStateBase() {};

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return PlayerState　更新終了時のステータスを返す
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
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	virtual void Enter(PlayerObject* _owner, float _deltaTime) {};

	/*
	@fn 地面移動処理関数
	@param	_owner 親クラスのポインタ
	@param	_keyState 入力情報
	*/
	void GroundMove(PlayerObject* _owner, const InputState& _keyState);

	/*
	@fn 入力チェック処理関数
	@param	_owner 親クラスのポインタ
	@param	_keyState 入力情報
	*/
	void CheckInput(PlayerObject* _owner, const InputState& _keyState);
	
	/*
	@fn 死亡状態か確認する関数
	@param	_owner 親クラスのポインタ
	*/
	void CheckDeadFlag(PlayerObject* _owner);

	/*
	@fn タイムオーバーか確認する関数
	*/
	void CheckTimeOverFlag();

	/*
	@fn 回転処理関数
	@param	_owner 親クラスのポインタ
	@param	_forward 回転させる方向ベクトル
	@param	_tmpForward 回転させる前の方向ベクトル
	*/
	void RotationProcess(PlayerObject* _owner,Vector3 _forward,Vector3 _tmpForward);

	/*
	@fn アナログスティック処理関数
	@param	_keyState 入力情報
	*/
	Vector3 CheckControllerAxis(const InputState& _keyState);

protected:
	
	/*
	@fn ジャンプ系のステータスの時入力がある場合の処理関数
	@param	_owner 親クラスのポインタ
	@param	_axis 補正済みのアナログスティック情報
	*/
	void InputJumpMovableProcess(PlayerObject* _owner, Vector3 _axis);

	// 親クラスのポインタを格納するためのSkeletalMeshComponentのポインタ変数
	SkeletalMeshComponent* skeletalMeshComponent;
	// stateの遷移を行うための変数
	PlayerState state;
	// 速度をポジションに作用する速度を格納するためのVector3変数
	Vector3 velocity;
	// 速度を格納するための変数
	float moveSpeed;
	// 入力制限の値を格納するための変数
	float inputDeadSpace;
	// 移動速度の最高値
	const float MaxMoveSpeed;
	// 最大落下速度の規定値
	const float MaxFallSpeed;

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
};

