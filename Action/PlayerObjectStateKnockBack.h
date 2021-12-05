#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateKnockBack.h
@brief ノックバック開始からアイドリング状態に移行するまでを管理
*/
class PlayerObjectStateKnockBack :
    public PlayerObjectStateBase
{
public:
	
	/*
	@fn コンストラクタ
	*/
	PlayerObjectStateKnockBack(PlayerObject* _owner);

	/*
	@fn デストラクタ
	*/
	~PlayerObjectStateKnockBack()override;

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
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
	// ノックバックの速度定数
	const float KnockBackSpeed;
	// ノックバックする時間定数
	const int KnockBackTime;
};

