#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"

/*
@file NormalEnemyObjectStateIdle.h
@brief 動かない敵オブジェクトのアイドリング状態を管理するクラス
*/
class NormalEnemyObjectStateIdle :
    public EnemyObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	NormalEnemyObjectStateIdle();

	/*
	@fn デストラクタ
	*/
	~NormalEnemyObjectStateIdle()override;

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return EnemyState 次のステータス
	*/
	EnemyState Update(EnemyObjectBase* _owner, float _deltaTime)override;

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Enter(EnemyObjectBase* _owner, float _deltaTime)override;

private:

};