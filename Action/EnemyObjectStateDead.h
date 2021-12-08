#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"

/*
@file EnemyObjectStateDead.h
@brief 敵オブジェクトの死亡状態を管理するクラス
*/
class EnemyObjectStateDead :
    public EnemyObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	EnemyObjectStateDead(EnemyObjectBase* _owner);

	/*
	@fn デストラクタ
	*/
	~EnemyObjectStateDead()override;

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

	// playerのポインタを保存するポインタ変数
	GameObject* playerObject;
	// 吹っ飛ぶ方向ベクトル
	Vector3 blowAwayDirection;

	// 死亡状態の時間をカウント
	int frameCount;
	// リスポーンする時間定数
	const int RespawnTime;
	// 描画をオフにする時間定数
	const int InvisibleTime;
	// 吹っ飛び力
	const float BlowAwayPower;
	// 吹っ飛び初速
	const float FirstBlowAwayPower;
	// 最大速度
	const float MaxSpeed;
};