#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SpriteComponent;

/*
@file ContinueSprite.h
@brief コンテニュー用画像を表示する
*/
class ContinueSprite :
    public GameObject
{
public:

    ContinueSprite();
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~ContinueSprite();
    
    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

    /*
    @brief	入力
    @param	入力情報
    */
    void GameObjectInput(const InputState& _keyState)override;

    /*
    @brief	drawFlagを見るためのgetter関数
    @return	drawFlag
    */
    static bool GetDrawFlag() { return drawFlag; }
    
    /*
    @brief	コンテニューしたかどうかフラグを見るためのgetter関数
    @return	continueFlag
    */
    static bool GetContinueFlag() { return continueFlag; }


private:

    // スプライトComponent
    SpriteComponent* sprite;
    // フレームカウント
    int frameCount;
    // 描画するかどうかフラグ
    bool visibleFlag;
    // 描画されているかフラグ
    static bool drawFlag;
    // コンテニューしたかどうかフラグ
    static bool continueFlag;

};

