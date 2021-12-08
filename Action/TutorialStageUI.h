#pragma once
//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "GameObject.h"
#include "SDL_TTF.h"

// クラスの前方宣言
class PlayerObject;

/*
@file FirstStageUI.h
@brief FirstStageのUI表示を行う
*/
class TutorialStageUI :
    public GameObject
{
public:

    /*
    @fn コンストラクタ
    @brief  objectの生成を行う
    */
    TutorialStageUI();
    
    /*
    @fn デストラクタ
    @brief  objectの削除を行う
    */
    ~TutorialStageUI();
    
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
    // スカイボックスクラスのポインタ変数
    class SkyBoxObject* skyBox;
};
