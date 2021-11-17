#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SpriteComponent;

/*
@file TitleBackGroundSprite.h
@brief タイトルの背景を表示する
*/
class TitleSprite :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    */
    TitleSprite();
   
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~TitleSprite();
    
    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // 背景用スプライトComponent
    SpriteComponent* sprite;
};

