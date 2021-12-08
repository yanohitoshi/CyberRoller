#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TitlePlayerStateBase.h"

/*
@file TitlePlayerStateJumpAttack.h
@brief タイトルシーン中でのジャンプアタック状態を管理するクラス
*/
class TitlePlayerStateJumpAttack :
    public TitlePlayerStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	TitlePlayerStateJumpAttack()
	: JumpAttackRotationAngle(10.0f)
	, JumpAttackTime(30)
	, ShiftPositionZ(100.0f)
	, Offset(400.0f){};

	/*
	@fn デストラクタ
	*/
	~TitlePlayerStateJumpAttack() {};

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

	// タイトル画面でのジャンプアタックプレイヤークラスのポインタ
	TitleJumpAttackPlayerObject* titleJumpAttackPlayerObject;

	// stateに入ってきたときのポジション
	Vector3 enterPosition;
	// 回転角度
	float rotationAngle;
	// フレーム時間を数えるカウント
	int frameCount;
	// 間隔
	const float Offset;
	// ジャンプ攻撃する時間
	const int JumpAttackTime;
	// 回転角定数
	const float JumpAttackRotationAngle;
	// Z軸をずらすための定数
	const float ShiftPositionZ;
};

