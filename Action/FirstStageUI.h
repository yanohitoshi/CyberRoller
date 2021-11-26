#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

class CollectionObject;
class CollectionUI;

/*
@file SecondStageUI.h
@brief SecondStageのUI表示を行う
*/
class FirstStageUI :
    public GameObject
{
public:
    
    /*
    @fn コンストラクタ
    @brief  objectの生成を行う
    @param	_playerObject プレイヤークラスのポインタ
    @param	_first 1つ目の収集物オブジェクトのポインタ
    @param	_second 2つ目の収集物オブジェクトのポインタ
    @param	_third 3つ目の収集物オブジェクトのポインタ
    */
    FirstStageUI(PlayerObject* _playerObject,CollectionObject* _first, CollectionObject* _second, CollectionObject* _third);
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~FirstStageUI();

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

    // 各収集物のUIクラスのポインタ
    CollectionUI* firstCollectionUI;
    CollectionUI* secondCollectionUI;
    CollectionUI* thirdCollectionUI;

    // それぞれの収集物の結果を表示する時間
    const int FirstDrawTime;
    const int SecondDrawTime;
    const int ThirdDrawTime;

    // それぞれの収集物の結果を表示する場所
    const Vector3 FirstCollectionPosition;
    const Vector3 SecondCollectionPosition;
    const Vector3 ThirdCollectionPosition;

    // クリア後のカウントを数える変数
    int clearCount;
    // ポジションが変更されているかどうか
    bool isChangePosition;
};

