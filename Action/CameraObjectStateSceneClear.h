#pragma once
#include "CameraObjectStateBase.h"

/*
@file GameObject.h
@brief ゲームオブジェクトの基底クラス
*/
class CameraObjectStateSceneClear :
    public CameraObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	CameraObjectStateSceneClear()
	: GameClearRadius(1000.0f)
	, AutomaticMoveSpeed(0.02f)
	, TrackingTime(60)
	, InitYaw(180.0f){};

	/*
	@fn デストラクタ
	*/
	~CameraObjectStateSceneClear() {};

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return PlayerState　更新終了時のステータスを返す
	*/
	CameraState Update(CameraObjectBase* _owner, float _deltaTime)override;


	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Enter(CameraObjectBase* _owner, float _deltaTime)override;

private:

	float yaw;
	// ステータス開始時のヨーの値定数
	const float InitYaw;

	const float GameClearRadius;
	// 自動回転する際の移動速度
	const float AutomaticMoveSpeed;
	int trackingCount;
	const int TrackingTime;
	float stopPisitionZ;
};

