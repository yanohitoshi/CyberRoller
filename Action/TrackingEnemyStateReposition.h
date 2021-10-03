#pragma once
#include "EnemyObjectStateBase.h"

/*
@file TrackingEnemyStateReposition.h
@brief 追跡する敵オブジェクトの追跡場所から元の位置に戻るまでを管理するクラス
*/
class TrackingEnemyStateReposition :
    public EnemyObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	TrackingEnemyStateReposition();

	/*
	@fn デストラクタ
	*/
	~TrackingEnemyStateReposition()override;

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

	Vector3 firstPosition;
	Vector3 repositionRotationVec;
};

