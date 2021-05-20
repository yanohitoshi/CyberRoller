#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SpriteComponent;

/*
@file ThankYouSprite.h
@brief リザルト画面を表示する
*/
class ThankYouSprite :
    public GameObject
{
public:
    
    /*
    @brief	コンストラクタ
    */
    ThankYouSprite();
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~ThankYouSprite();

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

    // 描画するかどうかフラグ
    bool visibleFlag;

};

