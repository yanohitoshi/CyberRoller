#pragma once
#include "PlayerObjectStateBase.h"

class SkeletalMeshComponent;

class PlayerObjectStateJumpStart :
    public PlayerObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	PlayerObjectStateJumpStart();

	/*
	@fn デストラクタ
	*/
	~PlayerObjectStateJumpStart()override;

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

	// ジャンプが行われているフレームを測るカウント変数
	int jumpFrameCount;
	// ジャンプが終了したかどうかのフラグ変数
	bool endFlag;
	// 落下速度の規定値
	const float MaxFallSpeed;
	// ジャンプ中に移動速度を徐々に減らすための計算に使う補正値
	const float JumpCorrection;
	// スイッチジャンプ中に移動速度を徐々に減らすための計算に使う補正値
	const float SwitchJumpCorrection;
	// ジャンプ力の加速度
	const float JumpAccelPower;
	// ジャンプボタン利用可能タイム
	const int JumpTime;
	// スイッチジャンプ利用可能タイム
	const int SwitchJumpTime;
};

