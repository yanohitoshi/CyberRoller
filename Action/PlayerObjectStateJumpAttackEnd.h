#pragma once
#include "PlayerObjectStateBase.h"

class PlayerObjectStateJumpAttackEnd :
    public PlayerObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	PlayerObjectStateJumpAttackEnd();

	/*
	@fn デストラクタ
	*/
	~PlayerObjectStateJumpAttackEnd()override;

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

	Vector3 jumpAttackDirection;
	GameObject* attackTargetEnemy;

	// ジャンプが行われているフレームを測るカウント変数
	int jumpFrameCount;
	// ジャンプが終了したかどうかのフラグ変数
	bool endFlag;
	// スイッチジャンプ時のジャンプ力の加速度
	const float SuccessJumpAccelPower;
	// スイッチジャンプ利用可能タイム
	const int SuccessJumpTime;
};

