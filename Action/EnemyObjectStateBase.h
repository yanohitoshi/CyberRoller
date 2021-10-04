#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectBase.h"
#include "SkeletalMeshComponent.h"

// クラスの前方宣言
class EnemyObjectBase;
class SkeletalMeshComponent;

/*
@enum　EnemyState 敵オブジェクトのステータス判別用
*/
enum class EnemyState
{
	// 待機状態
	ENEMY_STATE_IDLE = 0,
	// 死亡状態
	ENEMY_STATE_DEAD,
	// 復帰待機
	ENEMY_STATE_RESPAWN,
	// 攻撃
	ENEMY_STATE_ATTACK,
	// 移動状態
	ENEMY_STATE_MOVING,
	// ターン
	ENEMY_STATE_TURN,
	// 追跡
	ENEMY_STATE_TRACKING,
	// リポジション
	ENEMY_STATE_REPOSITION,
	// 総アニメーション数
	ENEMY_STATE_NUM,
};

/*
@file EnemyObjectStateBase.h
@brief 敵オブジェクトのステータスを管理するクラスの基底クラス
*/
class EnemyObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	EnemyObjectStateBase()
		: MaxFallSpeed(-2000.0f)
		, MaxMoveSpeed(1600.0f)
	{};

	/*
	@fn デストラクタ
	*/
	virtual ~EnemyObjectStateBase() {};

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return PlayerState　更新終了時のステータスを返す
	*/
	virtual EnemyState Update(EnemyObjectBase* _owner, float _deltaTime) = 0;

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	virtual void Enter(EnemyObjectBase* _owner, float _deltaTime) {};

	/*
	@fn 前方ベクトルを用いてキャラクターを回転させる関数
	@param	_owner 親クラスのポインタ
	@param	_forward 今のフレームの前方ベクトル
	@param	_tmpForward 前のフレームの前方ベクトル
	*/
	void RotationProcess(EnemyObjectBase* _owner, Vector3 _forward, Vector3 _tmpForward);

protected:

	// 親クラスのポインタを格納するためのSkeletalMeshComponentのポインタ変数
	SkeletalMeshComponent* skeletalMeshComponent;
	// stateの遷移を行うための変数
	EnemyState state;
	// 速度をポジションに作用する速度を格納するためのVector3変数
	Vector3 velocity;
	// 速度を格納するための変数
	float moveSpeed;
	// 入力制限の値を格納するための変数
	float inputDeadSpace;
	// 移動速度の最高値
	const float MaxMoveSpeed;
	// 最大落下速度の規定値
	const float MaxFallSpeed;

private:

};

