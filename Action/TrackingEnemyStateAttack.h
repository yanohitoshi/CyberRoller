#pragma once
#include "EnemyObjectStateBase.h"

/*
@file TrackingEnemyStateAttack.h
@brief 追跡する敵オブジェクトの攻撃状態を管理するクラス
*/
class TrackingEnemyStateAttack :
    public EnemyObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	TrackingEnemyStateAttack();

	/*
	@fn デストラクタ
	*/
	~TrackingEnemyStateAttack()override;

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	EnemyState Update(EnemyObjectBase* _owner, float _deltaTime)override;

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Enter(EnemyObjectBase* _owner, float _deltaTime)override;

private:

	// 追跡対象のオブジェクトのポインタ
	GameObject* trackingObject;
	// 追跡する方向
	Vector3 trackingRotationVec;
	// 初期ポジション
	Vector3 firstPosition;
	// 攻撃時の移動速度
	const float AttcakMoveSpeed;
};

