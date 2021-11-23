#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TitlePlayerStateBase.h"

/*
@file TitlePlayerStateRun.h
@brief タイトルシーン中での走る状態を管理するクラス
*/
class TitlePlayerStateRun :
    public TitlePlayerStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	TitlePlayerStateRun()
	: JumpDelayTime(120)
	, CorrectionValuePositionY(5.0f){};

	/*
	@fn デストラクタ
	*/
	~TitlePlayerStateRun() {};

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
	
	/*
	@fn ジャンプディレイ処理関数
	@param	_owner 親クラスのポインタ
	*/
	void JumpDelayProcess(TitlePlayerObject* _owner);

	// 初期ポジションに戻ってきているかの判定を取るための値を補正する定数
	const float CorrectionValuePositionY;
	Vector3 initPosition;
	// ジャンプ可能か
	bool isAvailableJump;
	// ジャンプ待ち時間を数える
	int jumpDelayCount;
	// ジャンプ待ち時間
	const int JumpDelayTime;
	// ジャンプ時間を数えるカウント
	int jumpCount;
};

