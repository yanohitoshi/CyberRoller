#pragma once
#include "TitlePlayerStateBase.h"

class TitlePlayerStateRun :
    public TitlePlayerStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	TitlePlayerStateRun()
	: JumpDelayTime(120){};

	/*
	@fn デストラクタ
	*/
	~TitlePlayerStateRun() {};

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return PlayerState　更新終了時のステータスを返す
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
	*/
	void JumpDelayProcess(TitlePlayerObject* _owner);

	int jumpDelayCount;
	int jumpCount;
	const int JumpDelayTime;
};

