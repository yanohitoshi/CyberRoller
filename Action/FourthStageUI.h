#pragma once
#include "GameObject.h"

class CollectionObject;
class CollectionUI;

class FourthStageUI :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @brief  objectの生成を行う
    @param	_playerObject プレイヤークラスのポインタ
    */
    FourthStageUI(PlayerObject* _playerObject, CollectionObject* _first, CollectionObject* _second, CollectionObject* _third);

    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~FourthStageUI();

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;


private:

    // シーンの時間制限の値
    const int SceneTime;
    // スカイボックスクラスのポインタ変数
    class SkyBoxObject* skyBox;

    PlayerObject* playerObject;

    CollectionUI* firstCollectionUI;
    CollectionUI* secondCollectionUI;
    CollectionUI* thirdCollectionUI;

    int clearCount;
    bool isChangePosition;
};

