#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CameraObjectStateBase.h"

/*
@file CameraObjectStateGameOver.h
@brief カメラのゲームオーバー状態を更新するクラス
*/
class CameraObjectStateGameOver :
    public CameraObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	CameraObjectStateGameOver()
		: GameOverRadius(400.0f)
		, AutomaticMoveSpeed(0.01f)
		, InitYaw(180.0f) 
		, OffsetZ(600.0f){};

	/*
	@fn デストラクタ
	*/
	~CameraObjectStateGameOver() {};

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

	// ヨー変数
	float yaw;
	// ステータス開始時のヨーの値定数
	const float InitYaw;
	// ゲームオーバー時の半径定数
	const float GameOverRadius;
	// 自動回転する際の移動速度
	const float AutomaticMoveSpeed;
	// Z軸の間隔
	const float OffsetZ;
};

