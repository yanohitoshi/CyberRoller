#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateBase.h"

/*
@file ExplosionObjectStateStartExplosion.h
@brief 爆発するオブジェクトの爆発前の予備動作を管理するクラス
*/
class ExplosionObjectStateStartExplosion :
    public ExplosionObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	ExplosionObjectStateStartExplosion()
	: BlowAwaySpeed(1600.0f)
	, FirstColorChangeTime(15)
	, ExplosionStartTime(180){};

	/*
	@fn デストラクタ
	*/
	~ExplosionObjectStateStartExplosion() {};

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
	@fn 点滅処理
	*/
	void Flashing();

	// ジャンプアタックプレイヤーに当たったかどうか
	bool isHitJumpAttackPlayer;
	// 吹っ飛ぶ方向ベクトル
	Vector3 blowAwayDirection;

	// 爆発開始時間をカウント
	int explosionStart;

	// 色を変更する時間
	int colorChangeTime;
	// 赤かどうか
	bool isRed;
	// 吹っ飛ぶスピード定数
	const float BlowAwaySpeed;
	//最初の色変更する時間
	const int FirstColorChangeTime;

	// 爆発開始時間
	const int ExplosionStartTime;
};