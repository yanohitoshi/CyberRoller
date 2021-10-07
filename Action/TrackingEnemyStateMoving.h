#pragma once
#include "EnemyObjectStateBase.h"

// 現在のstatePatternの仕様空のクラスを追加しないといけない場合がありそのための空のクラスです。
// 改善方法模索中です。

/*
@file TrackingEnemyStateMoving.h
@brief 追跡する敵オブジェクトの移動状態を管理するクラス
*/
class TrackingEnemyStateMoving :
    public EnemyObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	TrackingEnemyStateMoving();

	/*
	@fn デストラクタ
	*/
	~TrackingEnemyStateMoving()override;

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

