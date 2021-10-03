#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"

/*
@file EnemyObjectStateRespawn.h
@brief 敵オブジェクトのリスポーン状態を管理するクラス
*/
class EnemyObjectStateRespawn :
    public EnemyObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	EnemyObjectStateRespawn();

	/*
	@fn デストラクタ
	*/
	~EnemyObjectStateRespawn()override;

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	EnemyState Update(EnemyObjectBase* _owner, float _deltaTime)override;

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Enter(EnemyObjectBase* _owner, float _deltaTime)override;

private:
	// リスポーン時の移動速度
	const float RespawnMoveSpeed;
	// 移動方向
	Vector3 moveDirection;
	// 今のポジション
	Vector3 nowPosition;
};

