#pragma once
#include "ExplosionObjectStateBase.h"

class ExplosionObjectStateStartExplosion :
    public ExplosionObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	ExplosionObjectStateStartExplosion()
	: BlowAwaySpeed(1000.0f)
	, FirstColorChangeTime(15){};

	/*
	@fn デストラクタ
	*/
	~ExplosionObjectStateStartExplosion() {};

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
	
	/*
	@fn 点滅処理
	*/
	void Flashing();

	bool isHitJumpAttackPlayer;
	// 吹っ飛ぶ方向ベクトル
	Vector3 blowAwayDirection;

	int explosionStart;

	int colorChangeTime;
	bool isRed;
	const float BlowAwaySpeed;
	const int FirstColorChangeTime;
};