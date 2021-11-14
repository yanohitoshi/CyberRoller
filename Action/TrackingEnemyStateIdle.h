#pragma once
#include "EnemyObjectStateBase.h"

/*
@file TrackingEnemyStateIdle.h
@brief 追跡する敵オブジェクトのアイドリング状態を管理するクラス
*/
class TrackingEnemyStateIdle :
    public EnemyObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	TrackingEnemyStateIdle();

	/*
	@fn デストラクタ
	*/
	~TrackingEnemyStateIdle()override;

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

	// 待機時間
	const int StayTime;
	// 時間を計測
	int frameCount;
};

