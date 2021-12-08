#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateBase.h"

/*
@file ExplosionObjectStateRespawn.h
@brief 爆発するオブジェクトのリスポーン状態を管理するクラス
*/
class ExplosionObjectStateRespawn :
    public ExplosionObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	ExplosionObjectStateRespawn(){};

	/*
	@fn デストラクタ
	*/
	~ExplosionObjectStateRespawn() {};

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

	// リスポーン中のカウント変数
	int respawnCount;
	// 初期ポジション
	Vector3 firstPosition;
};

