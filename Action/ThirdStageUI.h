#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

/*
@file ThirdStageUI.h
@brief ThirdStageのUI表示を行う
*/
class ThirdStageUI :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @brief  objectの生成を行う
    */
    ThirdStageUI();
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~ThirdStageUI();

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

    // シーンの時間制限の値
    const int SCENE_TIME;

};

