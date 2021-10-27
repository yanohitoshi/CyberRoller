#pragma once
#include "GameObject.h"

class CollectionObject;
class CollectedSprite;
class UnCollectedSprite;
class CollectedEffectSprite;

class CollectionUI :
    public GameObject
{
public:
    
    /*
    @brief	コンストラクタ
    */
    CollectionUI(CollectionObject* _owner);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~CollectionUI()override;

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    CollectionObject* owner;
    CollectedSprite* collectedSprite;
    UnCollectedSprite* unCollectedSprite;
    CollectedEffectSprite* collectedEffectSprite;

};

