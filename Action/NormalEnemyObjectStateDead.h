#pragma once
#include "EnemyObjectStateBase.h"

class NormalEnemyObjectStateDead :
    public EnemyObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	NormalEnemyObjectStateDead();

	/*
	@fn デストラクタ
	*/
	~NormalEnemyObjectStateDead()override;

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

	int frameCount;

};

