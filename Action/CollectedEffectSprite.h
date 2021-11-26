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
@file CollectedEffectSprite.h
@brief 収集物を獲得したときのエフェクトを表示する
*/
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

    // 各収集物UIのポジション
    const Vector3 FirstCollectionPosition;
    const Vector3 SecondCollectionPosition;
    const Vector3 ThirdCollectionPosition;

    // 追加する拡大値
    const float AddScale;
    // 減らすalpha値
    const float SubAlpha;

public:

    /*
    @brief	SpriteComponentのgetter
    @return	SpriteComponentのポインタ
    */
    SpriteComponent* GetSpriteComponent() { return sprite; }

    void Reset();
};

