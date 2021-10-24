#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "TitlePlayerObject.h"

// クラスの前方宣言
class TitlePlayerObject;
class SkeletalMeshComponent;
class MeshComponent;

/*
@enum　TitlePlayerState
タイトルでのプレイヤーのステータス
*/
enum class TitlePlayerState
{
	RUN,
	JUMP_START,
	JUMP_LOOP,
	JUMP_ATTACK,
	STATE_NUM
};

/*
@file TitlePlayerStateBase.h
@brief タイトルシーン中でのプレイヤーのステータスを管理するクラスの基底クラス
*/
class TitlePlayerStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	TitlePlayerStateBase()
	: JumpLimitTime(13)
	, JumpSpeed(15.0f)
	, FirstJumpPower(40.0f)
	, Gravity(400.0f)
	, MaxFallSpeed(-200.0f){};

	/*
	@fn デストラクタ
	*/
	virtual ~TitlePlayerStateBase() {};

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return PlayerState　更新終了時のステータスを返す
	*/
	virtual TitlePlayerState Update(TitlePlayerObject* _owner, float _deltaTime) = 0;

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	virtual void Enter(TitlePlayerObject* _owner, float _deltaTime) {};

protected:

	// 親クラスのポインタを格納するためのSkeletalMeshComponentのポインタ変数
	SkeletalMeshComponent* skeletalMeshComponent;
	// 親クラスのポインタを格納するためのMeshComponentのポインタ変数
	MeshComponent* meshComponent;
	// stateの遷移を行うための変数
	TitlePlayerState state;
	Vector3 velocity;

	// ジャンプを続けるフレームカウント定数
	const float JumpLimitTime;
	const float JumpSpeed;
	const float FirstJumpPower;
	const float Gravity;
	const float MaxFallSpeed;
};

