#pragma once
#include "CameraObjectBase.h"

class AutoMoveCamera :
    public CameraObjectBase
{
public:

	/*
	@brief	コンストラクタ
	@param	ポジション
	@param	プレイヤーのポインタ
	*/
	AutoMoveCamera(const Vector3 _pos, PlayerObject* _playerObject);

	/*
	@fn デストラクタ
	@brief  objectの削除を行う
	*/
	~AutoMoveCamera();

	/*
	@fn アップデート関数
	@brief	更新処理を行う
	@param	_deltaTime 前のフレームでかかった時間
	*/
	void UpdateGameObject(float _deltaTime = 1.0f)override;

	/*
	@fn 入力を引数で受け取る更新関数
	@brief 基本的にここで入力情報を変数に保存しUpdateGameObjectで更新を行う
	@param	_keyState 入力情報
	*/
	void GameObjectInput(const InputState& _keyState)override;

private:

};

