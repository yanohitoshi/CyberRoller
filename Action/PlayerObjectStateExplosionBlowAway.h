#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateExplosionBlowAway.h
@brief 吹っ飛び開始からアイドリング状態に移行するまでを管理
*/
class PlayerObjectStateExplosionBlowAway :
    public PlayerObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	PlayerObjectStateExplosionBlowAway();

	/*
	@fn デストラクタ
	*/
	~PlayerObjectStateExplosionBlowAway()override;

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

	// ヒットした敵のポジション
	Vector3 hitEnemyPosition;
	// ノックバックする方向
	Vector3 knockBackDirection;
	// ノックバックの時間を数える
	int knockBackFrameCount;
	float knockBackSpeed;
	// ノックバックの速度定数
	const float KnockBackPower;
	// ノックバックする時間定数
	const int KnockBackTime;
	// 落下死亡ポジション
	const float FallDeadPositonZ;
};