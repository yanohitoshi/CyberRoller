#pragma once

#include "GameObject.h"

class SpriteComponent;

/*
@file TitleUI.h
@brief タイトル画面のUIを表示
*/

class TitleSceneUI :
    public GameObject
{
public:

    TitleSceneUI();
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~TitleSceneUI()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // タイトル画像表示用sprite
    SpriteComponent* sprite;

};

