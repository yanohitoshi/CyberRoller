#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ExplosionObjectBase.h"

// クラスの前方宣言
class MeshComponent;
class SoundEffectComponent;

/*
@enum　ExplosionObjectState 爆発物のステータス判別用
*/
enum class ExplosionObjectState
{
	// 待機状態
	IDLE = 0,
	// 落下状態
	FALL,
	// 爆発状態
	EXPLOSION,
	// 点滅状態
	EXPLOSION_START,
	// 復帰待機
	RESPAWN,
	// ステートの総数
	NUM,
};

/*
@file ExplosionObjectStateBase.h
@brief 爆発するオブジェクトの状態管理クラスの基底クラス
*/
class ExplosionObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	ExplosionObjectStateBase()
	: VerticalMoveSpeed(200.0f)
	, EmissiveColorRed(Color::Red)
	, EmissiveColorBlue(Color::LightBlue)
	, OriginalScale(0.5f)
	, SubScale(0.5f)
	, RespownTime(240)
	, ChangeRateTime(45)
	, SecondColorChangeTime(7)
	, ThirdColorChangeTime(3)
	, FirstChangeRateTime(60)
	, SecondChangeRateTime(120) {};

	/*
	@fn デストラクタ
	*/
	virtual ~ExplosionObjectStateBase() {};

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return ExplosionObjectState　更新終了時のステータスを返す
	*/
	virtual ExplosionObjectState Update(ExplosionObjectBase* _owner, float _deltaTime) = 0;

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	virtual void Enter(ExplosionObjectBase* _owner, float _deltaTime) {};

	/*
	@fn 前方ベクトルを用いてキャラクターを回転させる関数
	@param	_owner 親クラスのポインタ
	@param	_forward 今のフレームの前方ベクトル
	@param	_tmpForward 前のフレームの前方ベクトル
	*/
	void RotationProcess(ExplosionObjectBase* _owner,float _angle, Vector3 _axis);
	
	/*
	@fn 垂直移動処理
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void VerticalMove(ExplosionObjectBase* _owner, float _deltaTime);

protected:

	// 親クラスのポインタを格納するためのSkeletalMeshComponentのポインタ変数
	MeshComponent* meshComponent;
	// stateの遷移を行うための変数
	ExplosionObjectState state;

	// サウンドエフェクトクラス
	SoundEffectComponent* soundEffectComponent;

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

	// レートを変更するタイミング
	const int ChangeRateTime;

	// 縦移動する際の移動速度定数
	const float VerticalMoveSpeed;

	// エミッシブの色情報(赤)
	const Vector3 EmissiveColorRed;
	// エミッシブの色情報(青)
	const Vector3 EmissiveColorBlue;

	// 元もscale値
	const float OriginalScale;
	// scaleの減算値
	const float SubScale;

	// リスポーンするまでの時間
	const int RespownTime;

	// 二番目の色を変えるタイミング
	const int SecondColorChangeTime;
	// 三番目の色を変えるタイミング
	const int ThirdColorChangeTime;

	// 最初の色を変えるタイミングを変更する時間
	const int FirstChangeRateTime;
	// 二番目の色を変えるタイミングを変更する時間
	const int SecondChangeRateTime;

private:

};