#pragma once
#include "GameObject.h"

class SpriteComponent;
class Texture;
enum class CollectionTag;

class UnCollectedSprite :
    public GameObject
{
public:

    /*
    @brief	コンストラクタ
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

public:
    
    /*
    @brief	SpriteComponentのgetter
    @return	SpriteComponentのポインタ
    */
    SpriteComponent* GetSpriteComponent() { return sprite; }

};

