#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"

/*
@file SecondStageUI.h
@brief SecondStageのUI表示を行う
*/
class SecondStageUI :
    public GameObject
{
public:
    /*
    @fn コンストラクタ
    @brief  objectの生成を行う
    */
    SecondStageUI(PlayerObject* _playerObject);
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~SecondStageUI();

    /*
    @fn アップデート関数
    @brief	更新処理を行う
    @param	_deltaTime 前のフレームでかかった時間
    */
    void UpdateGameObject(float _deltaTime)override;

private:

    // シーンの時間制限の値
    const int SceneTime;
    class SkyBoxObject* skyBox;
};

