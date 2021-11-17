#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateBase.h"

/*
@file FallExplosionObjectStateIdle.h
@brief 落下する爆発物オブジェクトのアイドリング状態を管理するクラス
*/
class FallExplosionObjectStateIdle :
    public ExplosionObjectStateBase
{

public:

	/*
	@fn コンストラクタ
	*/
	FallExplosionObjectStateIdle() 
		: StayTime(10) {};

	/*
	@fn デストラクタ
	*/
	~FallExplosionObjectStateIdle(){};

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

	int stayCount;
	const int StayTime;
	float nowScaleZ;
};

