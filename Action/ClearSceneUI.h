#pragma once

#include "GameObject.h"

class SpriteComponent;

/*
@file ResultUI.h
@brief リザルト画面でのUIの表示を行う
*/

class ClearSceneUI :
    public GameObject
{
public:
    /*
    @fn コンストラクタ
    @brief  objectの生成を行う
    */
    ClearSceneUI();
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~ClearSceneUI();   

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // クリア画像表示用sprite
    SpriteComponent* sprite;

};

