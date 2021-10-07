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

    /*
    @brief	コンストラクタ
    */
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



private:

    /*
    @brief	入力情報を元に描画を切り替える
    @param	入力情報
    */
    void ChackKeyProcess(const InputState& _keyState);

    // スプライトComponent
    SpriteComponent* sprite;

    // 描画するかどうかフラグ
    bool visibleFlag;
    // 描画されているかフラグ
    static bool drawFlag;
    // コンテニューしたかどうかフラグ
    static bool continueFlag;

    // 描画を切り替えるカウント比較用の定数
    const int DrawCount;
    // フレームカウント
    int frameCount;

public://ゲッターセッター

    /*
    @fn drawFlagのgetter関数
    @brief	drawFlagを取得
    @return	描画されているかフラグ
    */
    static bool GetDrawFlag() { return drawFlag; }
    
    /*
    @fn continueFlagのgetter関数
    @brief	continueFlagを取得
    @return	コンテニューしたかどうかフラグ
    */
    static bool GetContinueFlag() { return continueFlag; }

};

