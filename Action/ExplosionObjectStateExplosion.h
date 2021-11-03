#pragma once
#include "ExplosionObjectStateBase.h"

class ExplosionObjectStateExplosion :
    public ExplosionObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	ExplosionObjectStateExplosion(){};

	/*
	@fn デストラクタ
	*/
	~ExplosionObjectStateExplosion() {};

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return PlayerState　更新終了時のステータスを返す
	*/
	ExplosionObjectState Update(ExplosionObject* _owner, float _deltaTime);

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Enter(ExplosionObject* _owner, float _deltaTime);

private:

	// 爆発の時間をカウントする変数
	int explosionCount;
};

