#pragma once
#include "CameraObjectStateBase.h"

/*
@file CameraObjectStateChangeMode.h
@brief カメラの画角変更モードを更新するクラス
*/
class CameraObjectStateChangeMode :
    public CameraObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	CameraObjectStateChangeMode()
	: SlowLrapTime(80){};

	/*
	@fn デストラクタ
	*/
	~CameraObjectStateChangeMode() {};

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return CameraState　更新終了時のステータスを返す
	*/
	CameraState Update(CameraObjectBase* _owner, float _deltaTime)override;

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Enter(CameraObjectBase* _owner, float _deltaTime)override;

private:

	// ステータス開始以降のカウントを数える
	int startStateCount;
	const int SlowLrapTime;
};

