#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "PlayerObjectStateBase.h"

/*
@file PlayerObjectStateDownStart.h
@brief ダウンスタートを管理
*/
class PlayerObjectStateDownStart :
    public PlayerObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	PlayerObjectStateDownStart();

	/*
	@fn デストラクタ
	*/
	~PlayerObjectStateDownStart()override;

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return PlayerState　更新終了時のステータスを返す
	*/
	PlayerState Update(PlayerObject* _owner, float _deltaTime)override;

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Enter(PlayerObject* _owner, float _deltaTime)override;

private:

};