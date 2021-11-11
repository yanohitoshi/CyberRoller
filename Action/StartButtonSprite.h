#pragma once
#include "GameObject.h"

// クラスの前方宣言
class SpriteComponent;

class StartButtonSprite :
    public GameObject
{
public:

    /*
    @brief	コンストラクタ
    */
    StartButtonSprite();

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~StartButtonSprite();

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // スプライトComponent
    SpriteComponent* sprite;

};

