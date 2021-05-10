#pragma once
#include "PlayerObjectStateBase.h"

class SkeletalMeshComponent;

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

	// ジャンプループが行われている時間を測るカウント変数
	int jumpLoopCount;
	// ジャンプスタートのアニメーションが終了するタイミングをずらすためのフラグ
	// ※見た目上ずらしたかったので作りました
	bool animChangeFlag;


	const float MaxFallSpeed;
};

