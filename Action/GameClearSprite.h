#pragma once
#include "GameObject.h"

class SpriteComponent;
/*
@file GameClearSprite.h
@brief ゲームクリア用画像を表示する
*/

class GameClearSprite :
    public GameObject
{
public:

    GameClearSprite();
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~GameClearSprite();
    
    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    SpriteComponent* sprite;
    int frameCount;
    bool visibleFlag;

};

