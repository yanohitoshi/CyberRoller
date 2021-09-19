#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "SDL_TTF.h"

class PlayerObject;

/*
@file FirstStageUI.h
@brief FirstStageのUI表示を行う
*/
class FirstStageUI :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @brief  objectの生成を行う
    */
    FirstStageUI();
    
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

    // ジャンプチュートリアルを表示する座標定数
    const Vector3 JumpTutorialPosition;
    // 移動チュートリアルを表示する座標定数
    const Vector3 MoveTutorialPosition;
    // ジャンプ攻撃チュートリアルを表示する座標定数
    const Vector3 JumpAttackTutorialPosition;

    class SkyBoxObject* skyBox;
};


