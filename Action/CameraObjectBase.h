#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

/*
@file CameraObjectBase.h
@brief GameObjectを継承したカメラの基底クラス
*/
class CameraObjectBase :
    public GameObject
{

public:

    /*
    @fn コンストラクタ
    @param	再利用するかフラグ
    @param	ObjectTag
    */
    CameraObjectBase(bool _reUseGameObject, const Tag _objectTag);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~CameraObjectBase();

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    virtual void UpdateGameObject(float _deltaTime = 1.0f);

    /*
    @fn 入力関数
    @brief	入力処理を行う
    @param	_keyState 入力情報
    */
    virtual void GameObjectInput(const InputState& _keyState);

private:

};

