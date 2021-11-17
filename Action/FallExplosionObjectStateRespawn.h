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
	FallExplosionObjectStateRespawn() {};

	/*
	@fn デストラクタ
	*/
	~FallExplosionObjectStateRespawn() {};

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return PlayerState　更新終了時のステータスを返す
	*/
	ExplosionObjectState Update(ExplosionObjectBase* _owner, float _deltaTime);

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Enter(ExplosionObjectBase* _owner, float _deltaTime);

private:

	void SetRandPosition(ExplosionObjectBase* _owner);
	void SetRandFallSpeed(ExplosionObjectBase* _owner);

	// リスポーン中のカウント変数
	int respawnCount;
	Vector3 firstPosition;
};

