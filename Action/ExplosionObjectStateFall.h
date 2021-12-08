#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ExplosionObjectStateBase.h"

/*
@file ExplosionObjectStateFall.h
@brief 落下状態を管理するクラス
*/
class ExplosionObjectStateFall :
    public ExplosionObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	ExplosionObjectStateFall()
		: FirstColorChangeTime(15){};

	/*
	@fn デストラクタ
	*/
	~ExplosionObjectStateFall() {};

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

	// 落下速度
	float fallSpeed;
	// 落下時間
	int fallCount;
	// 色を変える時間
	int colorChangeTime;
	// 赤色にするかどうか
	bool isRed;
	// 最初の色を変えるタイミング
	const int FirstColorChangeTime;
};

