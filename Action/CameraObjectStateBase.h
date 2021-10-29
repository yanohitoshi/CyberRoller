#pragma once
#include "CameraObjectBase.h"

enum class CameraState
{
	NORMAL,
	LANDSCAPE,
	DANCE,
	GAMEOVER,
	SCENECLEAR,
	NONE
};

class CameraObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	CameraObjectStateBase()
	: DeltaCorrection(8.0f){};

	/*
	@fn デストラクタ
	*/
	virtual ~CameraObjectStateBase() {};

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return PlayerState　更新終了時のステータスを返す
	*/
	virtual CameraState Update(CameraObjectBase* _owner, float _deltaTime) = 0;

	/*
	@fn インプット
	@brief	stateに応じて入力処理を行う
	@param	_owner 親クラスのポインタ
	@param	_keyState 入力情報
	*/
	virtual void Input(CameraObjectBase* _owner, const InputState& _keyState) {};

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	virtual void Enter(CameraObjectBase* _owner, float _deltaTime) {};

protected:

	// 線形保管時にデルタタイムをかけるとき用の補正定数
	const float DeltaCorrection;
	CameraState state;
	Vector3 offsetPosition;
};

