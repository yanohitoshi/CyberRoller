#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TitlePlayerStateBase.h"

/*
@file TitlePlayerStateJumpLoop.h
@brief タイトルシーン中でのジャンプループ状態を管理するクラス
*/
class TitlePlayerStateJumpLoop :
    public TitlePlayerStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	TitlePlayerStateJumpLoop()
	: OnGroundCoordinate(100.0f){};

	/*
	@fn デストラクタ
	*/
	~TitlePlayerStateJumpLoop() {};

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return TitlePlayerState　更新終了時のステータスを返す
	*/
	TitlePlayerState Update(TitlePlayerObject* _owner, float _deltaTime)override;

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Enter(TitlePlayerObject* _owner, float _deltaTime)override;

private:

	// 作用するジャンプ力
	float jumpPower;
	// ジャンプ時間を数えるカウント
	int jumpFrameCount;
	// 接地判定を取る座標値定数
	const float OnGroundCoordinate;
	// タイトル画面でのジャンプアタックプレイヤークラスのポインタ
	TitleJumpAttackPlayerObject* titleJumpAttackPlayerObject;
};

