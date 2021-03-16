#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SpriteComponent;

/*
@file GameOverSprite.h
@brief ゲームオーバーの時用のUIを表示する
*/
class GameOverSprite :
    public GameObject
{
public:

    GameOverSprite();
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~GameOverSprite();

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // スプライトComponent
    SpriteComponent* sprite;
    // フレームカウント
    int frameCount;
    // 描画するかフラグ
    bool visibleFlag;

};

