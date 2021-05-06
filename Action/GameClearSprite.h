#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SpriteComponent;
class PlayerObject;

/*
@file GameClearSprite.h
@brief ゲームクリア用画像を表示する
*/
class GameClearSprite :
    public GameObject
{
public:

    GameClearSprite(PlayerObject* _playerObject);
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~GameClearSprite();
    
    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    SpriteComponent* sprite;
    PlayerObject* playerObject;
    int frameCount;
    bool visibleFlag;

    // 描画を切り替えるカウント比較用の定数
    const int DRAW_COUNT;

};

