#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateBase.h"

/*
@file FallExplosionObjectStateRespawn.h
@brief 落下する爆発物オブジェクトのリスポーンを管理するクラス
*/
class FallExplosionObjectStateRespawn :
    public ExplosionObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	FallExplosionObjectStateRespawn()
	: MaxFallSpeed(1000.0f)
	, LowestFallSpeed(300.0f){};

	/*
	@fn デストラクタ
	*/
	~FallExplosionObjectStateRespawn() {};

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return ExplosionObjectState　更新終了時のステータスを返す
	*/
	ExplosionObjectState Update(ExplosionObjectBase* _owner, float _deltaTime);

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Enter(ExplosionObjectBase* _owner, float _deltaTime);

private:

	/*
	@fn ランダムなポジションをセット
	@param	_owner 親クラスのポインタ
	*/
	void SetRandPosition(ExplosionObjectBase* _owner);

	/*
	@fn ランダムな落下速度をセット
	@param	_owner 親クラスのポインタ
	*/
	void SetRandFallSpeed(ExplosionObjectBase* _owner);

	// リスポーン中のカウント変数
	int respawnCount;
	// 初期ポジション
	Vector3 firstPosition;

	// 最大落下速度
	const float MaxFallSpeed;
	// 落下速度の最低値
	const float LowestFallSpeed;
};

