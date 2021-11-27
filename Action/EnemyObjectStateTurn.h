#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"

/*
@file TrackingEnemyStateTurn.h
@brief 追跡する敵オブジェクトのターン状態を管理するクラス
*/
class EnemyObjectStateTurn :
    public EnemyObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	EnemyObjectStateTurn();

	/*
	@fn デストラクタ
	*/
	~EnemyObjectStateTurn()override;

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

};