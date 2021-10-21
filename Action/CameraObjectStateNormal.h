#pragma once
#include "CameraObjectStateBase.h"

class CameraObjectStateNormal :
    public CameraObjectStateBase
{
public:

	/*
	@fn コンストラクタ
	*/
	CameraObjectStateNormal() {};

	/*
	@fn デストラクタ
	*/
	~CameraObjectStateNormal() {};

	/*
	@fn アップデート
	@brief	stateに応じてアップデートを行う
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	@return PlayerState　更新終了時のステータスを返す
	*/
	CameraState Update(CameraObjectBase* _owner, float _deltaTime)override;

	/*
	@fn インプット
	@brief	stateに応じて入力処理を行う
	@param	_owner 親クラスのポインタ
	@param	_keyState 入力情報
	*/
	void Input(CameraObjectBase* _owner, const InputState& _keyState)override;

	/*
	@fn state変更時の初期化
	@param	_owner 親クラスのポインタ
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void Enter(CameraObjectBase* _owner, float _deltaTime)override;
};

