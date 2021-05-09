#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SpriteComponent;
class Texture;

/*
@file StartCountDownSprite.h
@brief ゲーム開始用カウントダウンを表示する
*/
class StartCountDownSprite :
    public GameObject
{
public:

    StartCountDownSprite();

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~StartCountDownSprite()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // スプライトComponent
    SpriteComponent* sprite;
    // texture 1用
    Texture* firstTexure;
    // texture 2用
    Texture* secondTexure;
    // texture 3用
    Texture* thirdTexure;
    // texture Start用
    Texture* startTexure;

    // texture変更フラグ
    bool texChangeFlag;
    // 描画フラグ
    bool drawSpriteFlag;

    // textureを切り替えるタイミング判定用の定数カウント
    const int ChangeCount;

    // フレームカウント
    int frameCount;
    // 表示時間
    int time;
    // カウントダウン開始するタイミングを見るためのカウント
    int timeStartCount;
};

