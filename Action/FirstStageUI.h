#pragma once
#include "GameObject.h"
#include "SDL_TTF.h"

/*
@file FirstStageUI.h
@brief FirstStageのUI表示を行う
*/

class FirstStageUI :
    public GameObject
{
public:
    /*
    @fn コンストラクタ
    @brief  objectの生成を行う
    */
    FirstStageUI();
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~FirstStageUI();
    
    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;
    
private:

};


