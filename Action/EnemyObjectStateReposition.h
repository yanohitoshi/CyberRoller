#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "EnemyObjectStateBase.h"

/*
@file EnemyObjectStateReposition.h
@brief 敵オブジェクトの追跡場所から元の位置に戻るまでを管理するクラス
*/
class EnemyObjectStateReposition :
    public EnemyObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	EnemyObjectStateReposition();

	/*
	@fn デストラクタ
	*/
	~EnemyObjectStateReposition()override;

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
	//初期ポジション
	Vector3 firstPosition;
	// 元のポジションに戻る際の方向
	Vector3 repositionRotationVec;
	// アイドリングへ移行する規定値
	const float IdlingLength;
};