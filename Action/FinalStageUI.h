#pragma once
#include "GameObject.h"

/*
@file FinalStageUI.h
@brief FinalStage画面でのUIの表示を行う
*/

class FinalStageUI :
    public GameObject
{
public:
    /*
    @fn コンストラクタ
    @brief  objectの生成を行う
    */
    FinalStageUI();
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~FinalStageUI();
    
    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;
    
    // タイムオーバー判定用フラグ
    static bool timeOverFlag;
    
    // カウントスタート判定用フラグ
    static bool countStartFlag;

private:

};

