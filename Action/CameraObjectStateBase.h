#pragma once
#include "CameraObjectBase.h"

/*
@enum class CameraState
	カメラの状態
*/
enum class CameraState
{
	// 通常状態
	NORMAL,
	// エリアによる画角変更状態
	CHANGEMODE,
	// ダンス中
	DANCE,
	// ゲームオーバー状態
	GAMEOVER,
	// クリア状態
	SCENECLEAR,
	// シーン開始状態
	SCENESTART,
	// 状態無し
	NONE
};

/*
@file CameraObjectStateBase.h
@brief カメラのステータスの基底クラス
*/
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
	@return CameraState　更新終了時のステータスを返す
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
	// ステータス変数
	CameraState state;
	// プレイヤーとの間隔
	Vector3 offsetPosition;
};

