#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SpriteComponent;
class Texture;
class Font;
class CountDownFont;

/*
@file CountDownBackFont.h
@brief カウントダウンの影の表示を行う
*/
class CountDownBackFont :
    public GameObject
{
public:

    /*
    @brief	コンストラクタ
    @param	カウントする時間
    */
    CountDownBackFont(CountDownFont* _owner,int _time);
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~CountDownBackFont();

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // SpriteComponent変数
    SpriteComponent* sprite;
    CountDownFont* owner;
    // フレームカウント
    int frameCount;
    // 計測する時間
    int time;

    // 時間を1進めるタイミングを比較する定数
    const int AddTimeCount;
};

