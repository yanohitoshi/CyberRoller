#pragma once
#include "EnemyObjectStateBase.h"

/*
@file EnemyObjectStateTracking.h
@brief 敵オブジェクトの追跡状態を管理するクラス
*/
class EnemyObjectStateTracking :
    public EnemyObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	EnemyObjectStateTracking(EnemyObjectBase* _owner);

	/*
	@fn デストラクタ
	*/
	~EnemyObjectStateTracking()override;

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return EnemyState 次のステータス
	*/
	EnemyState Update(EnemyObjectBase* _owner, float _deltaTime)override;

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Enter(EnemyObjectBase* _owner, float _deltaTime)override;

private:

	/*
	@brief	追跡中の移動処理
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void TrackingMove(EnemyObjectBase* _owner, float _deltaTime);

	// 追跡方向のベクトルの
	Vector3 trackingRotationVec;
	// 初期ポジション
	Vector3 firstPosition;
	// 追跡でどこまで近づくかの値
	const float TrackingLengthValue;
};