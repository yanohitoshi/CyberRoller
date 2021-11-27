#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"

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
	// 復帰する時間定数
	const int EndTime;
	const float BlowAwayPower;
	const float FirstBlowAwayPower;
	const float MaxSpeed;
	// 吹っ飛ぶ方向ベクトル
	Vector3 blowAwayDirection;
};