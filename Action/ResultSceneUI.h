#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

/*
@file ResultSceneUI.h
@brief ResultScene画面でのUIの表示を行う
*/
class ResultSceneUI :
    public GameObject
{
public:
    /*
    @fn コンストラクタ
    @brief  objectの生成を行う
    */
    ResultSceneUI();
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~ResultSceneUI();

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    class SkyBoxObject* skyBox;
};

