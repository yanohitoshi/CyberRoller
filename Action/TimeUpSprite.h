#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SpriteComponent;

/*
@file TimeUpSprite.h
@brief タイムオーバー用UIを表示
*/
class TimeUpSprite :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    */
    TimeUpSprite();
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~TimeUpSprite();

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

    /*
    @brief	描画されているかフラグのgetter
    @return	bool 描画されているかフラグ
    */

    static bool GetDrawFlag() { return drawFlag; }
private:

    // スプライトComponent
    SpriteComponent* sprite;
    // フレームカウント
    int frameCount;

    // 描画を切り替えるカウント比較用の定数
    const int DrawCount;

    // 1度だけ描画するためのフラグ
    bool visibleFlag;

    // 描画されているかフラグ
    static bool drawFlag;
};

