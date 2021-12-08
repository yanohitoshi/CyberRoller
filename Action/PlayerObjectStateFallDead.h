#pragma once
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateFallDead.h
@brief 落下死亡状態を管理
*/
class PlayerObjectStateFallDead :
    public PlayerObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	PlayerObjectStateFallDead();

	/*
	@fn デストラクタ
	*/
	~PlayerObjectStateFallDead()override;

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return PlayerState　更新終了時のステータスを返す
	*/
	PlayerState Update(PlayerObject* _owner, float _deltaTime)override;

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Enter(PlayerObject* _owner, float _deltaTime)override;

private:

	/*
	@fn 復帰遷移カウント処理関数
	@param	_owner 親クラスのポインタ
	*/
	void ToRespawnCountProcess(PlayerObject* _owner);

	// リスポーン状態に入るまでのカウントを測る変数
	int respawnCount;

	// リスポーン状態に入る時間
	const int RespawnTime;
};