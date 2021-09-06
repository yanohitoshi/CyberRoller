#pragma once

#include "EnemyObjectBase.h"

// クラスの前方宣言
class EnemyObjectBase;
class SkeletalMeshComponent;

/*
@enum　PlayerState
プレイヤーのステータス判別用
*/
enum class EnemyState
{
	// 待機
	ENEMY_STATE_IDLE = 0,
	// 走る
	ENEMY_STATE_RUN,
	// 走り状態から振り返り
	ENEMY_STATE_RUN_TURN,

	// 総アニメーション数
	ENEMY_STATE_NUM,
};

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

	///*
	//@fn 地面移動処理関数
	//@param	_owner 親クラスのポインタ
	//@param	_keyState 入力情報
	//*/
	//void GroundMove(EnemyObject* _owner, const InputState& _keyState);

	///*
	//@fn 回転処理関数
	//@param	_owner 親クラスのポインタ
	//@param	_keyState 入力情報
	//*/
	//void RotationProcess(EnemyObject* _owner, Vector3 _forward, Vector3 _tmpForward);

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

