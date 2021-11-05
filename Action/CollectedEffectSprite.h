#pragma once
#include "GameObject.h"

class SpriteComponent;
class Texture;
enum class CollectionTag;

class CollectedEffectSprite :
    public GameObject
{
public:

    /*
    @brief	コンストラクタ
    */
    CollectedEffectSprite(CollectionTag collectionTag);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~CollectedEffectSprite()override;

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
    float scale;
    float alpha;
public:

    /*
    @brief	SpriteComponentのgetter
    @return	SpriteComponentのポインタ
    */
    SpriteComponent* GetSpriteComponent() { return sprite; }

    void Reset();
};

