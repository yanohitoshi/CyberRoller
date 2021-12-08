#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SpriteComponent;
class CountDownFont;
class SoundEffectComponent;

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

    /*
    @fn フェードインアウトの状態を見る関数
    */
    void CheckFadeInOutProcess();
    
    /*
    @fn フェードインアウト処理関数
    */
    void FadeInOutProcess();
    
    /*
    @fn 最後のフェードアウト処理関数
    */
    void LastFadeOutProcess();
    
    /*
    @fn フェードインアウトの切り替え処理関数
    */
    void ChangeFadeProcess();

    // ownerを格納するためのポインタ変数
    CountDownFont* owner;
    // SpriteComponentのポインタ変数
    SpriteComponent* sprite;
    // サウンドエフェクトクラス
    SoundEffectComponent* soundEffect;

    // サウンドエフェクトを再生するかどうか
    bool isPlaySound;
    // fadein・outを切り替えるフラグ
    bool fadeFlag;
    // alpha値
    float alpha;
    // 何回fadeinしたかを数えるカウント
    int fadeinCount;

    // フェードインアウトに用いる値定数
    const float FadeValue;
    // フェードインに切り替える規定値定数
    const float ChangeFadeInValue;
    // フェードアウトに切り替える規定値定数
    const float ChangeFadeOutValue;
};
