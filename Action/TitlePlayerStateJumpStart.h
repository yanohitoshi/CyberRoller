#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TitlePlayerStateBase.h"

/*
@file TitlePlayerStateJumpStart.h
@brief タイトルシーン中でのジャンプ開始状態を管理するクラス
*/
class TitlePlayerStateJumpStart :
    public TitlePlayerStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	TitlePlayerStateJumpStart()
	{};

	/*
	@fn デストラクタ
	*/
	~TitlePlayerStateJumpStart() {};

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
	// ジャンプした回数
	int jumpCount;
};

