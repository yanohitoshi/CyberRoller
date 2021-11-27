#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"

/*
@file MoveEnemyObjectStateMoving.h
@brief 移動する敵オブジェクトの移動状態を管理するクラス
*/
class MoveEnemyObjectStateMoving :
    public EnemyObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	MoveEnemyObjectStateMoving();

	/*
	@fn デストラクタ
	*/
	~MoveEnemyObjectStateMoving()override;

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

	/*
	@fn 移動処理関数
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Move(EnemyObjectBase* _owner, float _deltaTime);

	// 移動方向
	Vector3 moveDirection;
	// 移動間隔
	float moveDistance;
	// 初期ポジション
	Vector3 firstPosition;

};