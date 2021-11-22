#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CameraObjectStateBase.h"

/*
@file CameraObjectStateSceneClear.h
@brief カメラのシーンクリア状態を更新するクラス
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
	, InitYaw(180.0f)
	, OffsetZ(400.0f){};

	/*
	@fn デストラクタ
	*/
	~CameraObjectStateSceneClear() {};

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
	// 追跡時間を数えるカウント変数
	int trackingCount;
	// 停止するZ軸ポジションを格納する変数
	float stopPisitionZ;
	// ステータス開始時のヨーの値定数
	const float InitYaw;
	// クリア時の回転する際の半径
	const float GameClearRadius;
	// 自動回転する際の移動速度
	const float AutomaticMoveSpeed;
	// 追跡する時間
	const int TrackingTime;
	// Z軸の間隔
	const float OffsetZ;
};

