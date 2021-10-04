#pragma once
#include "EnemyObjectStateBase.h"

class EnemyObjectStateAttack :
    public EnemyObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	EnemyObjectStateAttack();

	/*
	@fn デストラクタ
	*/
	~EnemyObjectStateAttack()override;

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

