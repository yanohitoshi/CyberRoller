#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"

/*
@file MoveEnemyObjectStateIdle.h
@brief 移動する敵オブジェクトのアイドリング状態を管理するクラス
*/
class MoveEnemyObjectStateIdle :
    public EnemyObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	MoveEnemyObjectStateIdle();

	/*
	@fn デストラクタ
	*/
	~MoveEnemyObjectStateIdle()override;

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