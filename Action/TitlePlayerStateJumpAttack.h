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

	TitleJumpAttackPlayerObject* titleJumpAttackPlayerObject;

	Vector3 enterPosition;
	float rotationAngle;
	int frameCount;
	const float Offset;
	const int JumpAttackTime;
	// 回転角定数
	const float JumpAttackRotationAngle;
	// Z軸をずらすための定数
	const float ShiftPositionZ;
};

