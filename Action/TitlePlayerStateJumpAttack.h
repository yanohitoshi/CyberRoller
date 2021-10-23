#pragma once
#include "TitlePlayerStateBase.h"
class TitlePlayerStateJumpAttack :
    public TitlePlayerStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	TitlePlayerStateJumpAttack()
	: JumpAttackRotationAngle(10.0f)
	, JumpAttackTime(10){};

	/*
	@fn デストラクタ
	*/
	~TitlePlayerStateJumpAttack() {};

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

	float rotationAngle;
	int frameCount;
	const int JumpAttackTime;
	// 回転角定数
	const float JumpAttackRotationAngle;
};

