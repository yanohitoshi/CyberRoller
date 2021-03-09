#pragma once

#include "GameObject.h"

class SpriteComponent;
class Texture;

/*
@file TimeSprite.h
@brief 時間表示フレーム用のUIを表示
*/

class TimeSprite :
    public GameObject
{
public:

    TimeSprite();
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~TimeSprite();

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // スプライトComponent
    SpriteComponent* sprite;
    // texture
    Texture* tex;
    // フレームカウント変数
    int frameCount;
};

