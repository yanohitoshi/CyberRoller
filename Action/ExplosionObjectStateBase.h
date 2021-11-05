#pragma once
#include "ExplosionObject.h"

class MeshComponent;


/*
@enum　ExplosionObjectState 爆発物のステータス判別用
*/
enum class ExplosionObjectState
{
	// 待機状態
	IDLE = 0,
	// 爆発状態
	EXPLOSION,
	// 点滅状態
	EXPLOSION_START,
	// 復帰待機
	RESPAWN,
	// ステートの総数
	NUM,
};


class ExplosionObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	ExplosionObjectStateBase()
	: VerticalMoveSpeed(100.0f)
	, EmissiveColorRed(Color::Red)
	, EmissiveColorBlue(Color::LightBlue){};

	/*
	@fn デストラクタ
	*/
	virtual ~ExplosionObjectStateBase() {};

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return PlayerState　更新終了時のステータスを返す
	*/
	virtual ExplosionObjectState Update(ExplosionObject* _owner, float _deltaTime) = 0;

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	virtual void Enter(ExplosionObject* _owner, float _deltaTime) {};

	/*
	@fn 前方ベクトルを用いてキャラクターを回転させる関数
	@param	_owner 親クラスのポインタ
	@param	_forward 今のフレームの前方ベクトル
	@param	_tmpForward 前のフレームの前方ベクトル
	*/
	void RotationProcess(ExplosionObject* _owner,float _angle, Vector3 _axis);

	void VerticalMove(ExplosionObject* _owner, float _deltaTime);

protected:

	// 親クラスのポインタを格納するためのSkeletalMeshComponentのポインタ変数
	MeshComponent* meshComponent;
	// stateの遷移を行うための変数
	ExplosionObjectState state;
	// 速度をポジションに作用する速度を格納するためのVector3変数
	Vector3 velocity;
	// 速度を格納するための変数
	float moveSpeed;

	// フレームをカウントする変数
	int frameCount;
	// 移動する速度に掛ける倍率
	float rate;
	// 角度
	float angle;
	// 縦移動する際の移動速度定数
	const float VerticalMoveSpeed;
	const Vector3 EmissiveColorRed;
	const Vector3 EmissiveColorBlue;

private:


};