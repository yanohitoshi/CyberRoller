#pragma once
#include "GameObject.h"

class SpriteComponent;
class Texture;
enum class CollectionTag;

class CollectedSprite :
    public GameObject
{
public:

    /*
    @brief	コンストラクタ
    */
    CollectedSprite(CollectionTag collectionTag);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~CollectedSprite()override;

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
    // フレームカウント変数
    int frameCount;

public:
    
    /*
    @brief	SpriteComponentのgetter
    @return	SpriteComponentのポインタ
    */
    SpriteComponent* GetSpriteComponent() { return sprite; }
};

