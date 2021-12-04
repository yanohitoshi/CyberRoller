#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

// クラスの前方宣言
class SkeletalMeshComponent;

/*
@file PlayerObjectStateJumpStart.h
@brief ジャンプ開始状態を管理
*/
class PlayerObjectStateJumpStart :
    public PlayerObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	PlayerObjectStateJumpStart(PlayerObject* _owner);

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

	/*
	@fn 入力チェック関数処理関数
	@param	_owner 親クラスのポインタ
	@param	_keyState 入力情報
	*/
	void CheckInputProcess(PlayerObject* _owner, const InputState& _keyState);

	/*
	@fn 入力がない場合の処理関数
	@param	_owner 親クラスのポインタ
	*/
	void UninputMovableProcess(PlayerObject* _owner);

	/*
	@fn ジャンプ開始処理関数
	@param	_owner 親クラスのポインタ
	*/
	void JumpStartProcess(PlayerObject* _owner);

	/*
	@fn ジャンプ終了準備処理関数
	@param	_owner 親クラスのポインタ
	*/
	void JumpEndProcess(PlayerObject* _owner);

	// ジャンプが行われているフレームを測るカウント変数
	int jumpFrameCount;
	// ジャンプが終了したかどうかのフラグ変数
	bool endFlag;
	// ジャンプ中に移動速度を徐々に減らすための計算に使う補正値
	const float JumpCorrection;
	// スイッチジャンプ中に移動速度を徐々に減らすための計算に使う補正値
	const float SwitchJumpCorrection;
	// ジャンプ力の加速度
	const float JumpAccelPower;
	// スイッチジャンプ時のジャンプ力の加速度
	const float SwitchJumpAccelPower;
	// ジャンプボタン利用可能タイム
	const int JumpTime;
	// スイッチジャンプ利用可能タイム
	const int SwitchJumpTime;
	// 初期化時にオーナーの速度に減速を掛ける定数
	const float Deceleration;

	// ステータスが切り替わった時に鳴らすサウンドエフェクトクラス
	SoundEffectComponent* switchJumpSoundEffect;
};

