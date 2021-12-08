#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

// クラスの前方宣言
class SkeletalMeshComponent;

/*
@file PlayerObjectStateRunStop.h
@brief 走りから停止を管理
*/
class PlayerObjectStateRunStop :
    public PlayerObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	PlayerObjectStateRunStop();

	/*
	@fn デストラクタ
	*/
	~PlayerObjectStateRunStop()override;

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

	// 振り返りに入れるかどうかの制限カウント
	int isTurnCount;
	// 減速力
	float decelerationForce;
	// 前回の行われたターンから間隔を空けるための規定値
	const int TurnDelayValue;
	// ターンに入れるカウントの規定値
	const int TurnValue;
};
