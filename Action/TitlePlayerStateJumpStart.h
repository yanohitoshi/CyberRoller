#pragma once
#include "TitlePlayerStateBase.h"
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
	// 作用するジャンプ力
	float jumpPower;
	int jumpFrameCount;
};

