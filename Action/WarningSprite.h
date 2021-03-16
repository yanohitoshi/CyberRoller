#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SpriteComponent;
class CountDownFont;

/*
@file WarningSprite.h
@brief 時間経過を知らせるUIを表示
*/
class WarningSprite :
    public GameObject
{
public:
    
    /*
    @fn コンストラクタ
    @brief	コンストラクタ 
    @param	親となるCountDownFont型ポインタ
    */
    WarningSprite(CountDownFont* _owner);
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~WarningSprite();

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:
    // ownerを格納するためのポインタ変数
    CountDownFont* owner;
    // SpriteComponentのポインタ変数
    SpriteComponent* sprite;
    // fadein・outを切り替えるフラグ
    bool fadeFlag;
    // alpha値
    float alpha;
    // 何回fadein・outしたかを数えるカウント
    int count;
};

