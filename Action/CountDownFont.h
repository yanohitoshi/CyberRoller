#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SpriteComponent;
class Texture;
class Font;

/*
@file CountDownFont.h
@brief カウントダウンフォントの表示を行う
*/
class CountDownFont
    : public GameObject
{
public:

    /*
    @brief	コンストラクタ
    @param	カウントする時間
    */
    CountDownFont(int _time);
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~CountDownFont();
    
    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;
    
    bool GetWarningFlag() { return warningFlag; }

    static bool timeOverFlag;
    static bool countStartFlag;

private:

    // SpriteComponent変数
    SpriteComponent* sprite;
    // フレームカウント
    int frameCount;
    // 計測する時間
    int time;
    // WarningSpriteClassを起動するかどうかフラグ
    bool warningFlag;

    // 時間を1進めるタイミングを比較する定数
    const int ADD_TIME_COUNT;
    // 時間制限の色を変更するタイミングを比較する定数
    const int CHANGE_COLOR_COUNT;
};