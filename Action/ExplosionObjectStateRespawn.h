#pragma once
#include "ExplosionObjectStateBase.h"

class ExplosionObjectStateRespawn :
    public ExplosionObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	ExplosionObjectStateRespawn()
		: MoveSpeed(50.0f) {};

	/*
	@fn デストラクタ
	*/
	~ExplosionObjectStateRespawn() {};

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

	int frameCount;
	float rate;
	float angle;
	const float MoveSpeed;
};

