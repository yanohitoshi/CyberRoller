#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

// クラスの前方宣言
class SpriteComponent;
class Texture;
enum class CollectionTag;

/*
@file UnCollectedSprite.h
@brief 収集物を獲得してない状態の画像を表示する
*/
class UnCollectedSprite :
    public GameObject
{
public:

    /*
    @brief	コンストラクタ
    @param 何番目の収集物かのタグ
    */
    UnCollectedSprite(CollectionTag collectionTag);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~UnCollectedSprite()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // スプライトComponent
    SpriteComponent* sprite;
    // texture
    Texture* tex;

    // 各収集物UIのポジション
    const Vector3 FirstCollectionPosition;
    const Vector3 SecondCollectionPosition;
    const Vector3 ThirdCollectionPosition;

public:
    
    /*
    @brief	SpriteComponentのgetter
    @return	SpriteComponentのポインタ
    */
    SpriteComponent* GetSpriteComponent() { return sprite; }

};

