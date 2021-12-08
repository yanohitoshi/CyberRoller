#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"

/*
@file EnhancedEnemyStateFlinch.h
@brief 強化敵オブジェクトの怯み状態を管理するクラス
*/
class EnhancedEnemyStateFlinch :
    public EnemyObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	EnhancedEnemyStateFlinch();

	/*
	@fn デストラクタ
	*/
	~EnhancedEnemyStateFlinch()override;

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

	// 怯み状態の時間をカウント
	int flinchCount;
	// 吹っ飛ぶ方向ベクトル
	Vector3 blowAwayDirection;

	// 復帰する時間定数
	const int EndTime;
	// 吹っ飛ぶ力定数
	const float BlowAwayPower;
	// 初期吹っ飛び力定数
	const float FirstBlowAwayPower;
	// 最大速度定数
	const float MaxSpeed;
};