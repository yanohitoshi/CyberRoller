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

	GameObject* trackingObject;
	Vector3 trackingRotationVec;
	Vector3 firstPosition;
};

